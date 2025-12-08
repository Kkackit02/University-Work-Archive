#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen_x86.h"

static int has_return_stmt(StmtList *body);

/* 32-bit x86 코드 생성기
 * - int 타입만
 * - 지역변수/매개변수는 모두 스택에 int(4바이트)로 저장
 * - 표현식은 eax를 결과 레지스터로 사용
 * - 함수 호출은 cdecl 호출 규약 따름
 */

typedef struct {
    const char *name;
    int offset;       /* ebp 기준 음수 오프셋 */
} Var;

static int find_var(const Var *vars, int n, const char *name) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(vars[i].name, name) == 0) return i;
    }
    return -1;
}

static void alloc_locals_and_params(Function *f, Var *vars, int *var_count, int *stack_size) {
    int count = 0;
    int local_offset = -4;
    int param_offset = 8;

    /* 매개변수 먼저 (ebp+8, ebp+12, ...) */
    if (f->params) {
        Param *p = f->params->head;
        while (p) {
            vars[count].name = p->name;
            vars[count].offset = param_offset;
            count++;
            param_offset += 4;
            p = p->next;
        }
    }

    /* 지역변수: stmt_list를 훑으면서 vardecl 수집 (ebp-4, ebp-8, ...) */
    if (f->body) {
        Stmt *s = f->body->head;
        while (s) {
            if (s->kind == STMT_VARDECL) {
                if (find_var(vars, count, s->u.vardecl.var_name) < 0) {
                    vars[count].name = s->u.vardecl.var_name;
                    vars[count].offset = local_offset;
                    count++;
                    local_offset -= 4;
                }
            } else if (s->kind == STMT_FOR) {
                if (s->u.for_stmt.init && s->u.for_stmt.init->kind == STMT_VARDECL) {
                    if (find_var(vars, count, s->u.for_stmt.init->u.vardecl.var_name) < 0) {
                        vars[count].name = s->u.for_stmt.init->u.vardecl.var_name;
                        vars[count].offset = local_offset;
                        count++;
                        local_offset -= 4;
                    }
                }
            }
            s = s->next;
        }
    }
    
    *var_count = count;
    *stack_size = (-local_offset) - 4;
}

static void gen_expr(Expr *e, Var *vars, int var_count);

static void gen_stmt(Stmt *s, Var *vars, int var_count, const char *func_name);

/* 변수 위치에서 eax 로드 */
static void load_var_to_eax(const char *name, Var *vars, int var_count) {
    int idx = find_var(vars, var_count, name);
    if (idx < 0) {
        fprintf(stderr, "Unknown variable: %s\n", name);
        exit(1);
    }
    int off = vars[idx].offset;
    printf("    movl %d(%%ebp), %%eax\n", off);
}

static void gen_binop(Expr *e, Var *vars, int var_count) {
    /* rhs 먼저, lhs 나중 */
    gen_expr(e->u.binop.rhs, vars, var_count);  /* eax = rhs */
    printf("    pushl %%eax\n");
    gen_expr(e->u.binop.lhs, vars, var_count);  /* eax = lhs */
    printf("    popl %%ecx\n");                 /* ecx = rhs */

    switch (e->u.binop.op) {
    case BIN_ADD:
        printf("    addl %%ecx, %%eax    # lhs + rhs\n");
        break;
    case BIN_SUB:
        printf("    subl %%ecx, %%eax    # lhs - rhs\n");
        break;
    case BIN_MUL:
        printf("    imull %%ecx, %%eax   # lhs * rhs\n");
        break;
    case BIN_DIV:
        /* lhs / rhs, lhs=eax, rhs=ecx */
        printf("    cdq                  # sign-extend eax -> edx:eax\n");
        printf("    idivl %%ecx          # lhs / rhs, quotient in eax\n");
        break;
    case BIN_EQ:
    case BIN_NE:
    case BIN_LT:
    case BIN_GT:
    case BIN_LE:
    case BIN_GE:
        printf("    cmpl %%ecx, %%eax\n");
        printf("    movl $0, %%eax\n"); // 일단 eax를 0으로 초기화
        if (e->u.binop.op == BIN_EQ) printf("    sete %%al\n");
        if (e->u.binop.op == BIN_NE) printf("    setne %%al\n");
        if (e->u.binop.op == BIN_LT) printf("    setl %%al\n");
        if (e->u.binop.op == BIN_GT) printf("    setg %%al\n");
        if (e->u.binop.op == BIN_LE) printf("    setle %%al\n");
        if (e->u.binop.op == BIN_GE) printf("    setge %%al\n");
        break;
    default:
        printf("    # unknown binop\n");
        break;
    }
}

static void gen_call(Expr *e, Var *vars, int var_count) {
    int argc = 0;
    ExprList *arg_list = e->u.call.args;
    
    // 1. 인자들을 역순으로 스택에 push
    // 연결 리스트를 뒤집는 대신, 재귀적으로 처리하여 역순 push 효과
    void push_args_reverse(ExprList* args) {
        if (!args) return;
        push_args_reverse(args->next);
        gen_expr(args->expr, vars, var_count);
        printf("    pushl %%eax\n");
    }

    ExprList *cur = arg_list;
    while(cur) {
        argc++;
        cur = cur->next;
    }

    push_args_reverse(arg_list);

    printf("    call _%s\n", e->u.call.func_name);
    
    // 3. 스택 정리 (cdecl)
    if (argc > 0) {
        printf("    addl $%d, %%esp\n", argc * 4);
    }
    /* 반환값은 eax에 있음 */
}

static void gen_expr(Expr *e, Var *vars, int var_count) {
    if (!e) return;

    switch (e->kind) {
    case EXPR_INT:
        printf("    movl $%d, %%eax\n", e->u.int_value);
        break;
    case EXPR_VAR:
        load_var_to_eax(e->u.var_name, vars, var_count);
        break;
    case EXPR_BINOP:
        gen_binop(e, vars, var_count);
        break;
    case EXPR_CALL:
        gen_call(e, vars, var_count);
        break;
    case EXPR_ASSIGN: {
        gen_expr(e->u.assign_expr.value, vars, var_count); /* eax = value */
        int idx = find_var(vars, var_count, e->u.assign_expr.var_name);
        if (idx < 0) {
            fprintf(stderr, "Unknown variable in assign expr: %s\n", e->u.assign_expr.var_name);
            exit(1);
        }
        int off = vars[idx].offset;
        printf("    movl %%eax, %d(%%ebp)   # %s = eax (assign expr)\n", off, e->u.assign_expr.var_name);
        break;
    }
    default:
        printf("    # unknown expr kind\n");
        break;
    }
}

static void gen_stmt(Stmt *s, Var *vars, int var_count, const char *func_name) {
    if (!s) return;

    switch (s->kind) {
    case STMT_VARDECL: {
        printf("    # var %s\n", s->u.vardecl.var_name);
        if (s->u.vardecl.initial_value) {
            gen_expr(s->u.vardecl.initial_value, vars, var_count); /* eax = initial_value */
            int idx = find_var(vars, var_count, s->u.vardecl.var_name);
            if (idx < 0) {
                fprintf(stderr, "Unknown variable in vardecl with init: %s\n", s->u.vardecl.var_name);
                exit(1);
            }
            int off = vars[idx].offset;
            printf("    movl %%eax, %d(%%ebp)   # %s = eax (initialization)\n", off, s->u.vardecl.var_name);
        }
        break;
    }
    case STMT_ASSIGN: {
        gen_expr(s->u.assign.value, vars, var_count); /* eax = value */
        int idx = find_var(vars, var_count, s->u.assign.var_name);
        if (idx < 0) {
            fprintf(stderr, "Unknown variable in assign: %s\n", s->u.assign.var_name);
            exit(1);
        }
        int off = vars[idx].offset;
        printf("    movl %%eax, %d(%%ebp)   # %s = eax\n", off, s->u.assign.var_name);
        break;
    }
    case STMT_EXPR:
        gen_expr(s->u.expr, vars, var_count);
        break;
    case STMT_RETURN:
        gen_expr(s->u.expr, vars, var_count);   /* eax = return value */
        printf("    jmp .Lend_%s\n", func_name);
        break;
    case STMT_IF: {
        static int if_count = 0;
        int current_if_id = if_count++;
        char else_label[64], end_if_label[64];
        snprintf(else_label, sizeof(else_label), ".L_else_%d", current_if_id);
        snprintf(end_if_label, sizeof(end_if_label), ".L_endif_%d", current_if_id);

        gen_expr(s->u.if_stmt.cond, vars, var_count); // 조건 평가, 결과는 eax에
        printf("    cmpl $0, %%eax\n"); // eax가 0이면 거짓
        if (s->u.if_stmt.else_body) {
            printf("    je %s\n", else_label); // 거짓이면 else_label로 점프
        } else {
            printf("    je %s\n", end_if_label); // 거짓이면 endif_label로 점프 (else 없음)
        }

        // then_body
        if (s->u.if_stmt.then_body) {
            Stmt *current_then_stmt = s->u.if_stmt.then_body->head;
            while (current_then_stmt) {
                gen_stmt(current_then_stmt, vars, var_count, func_name);
                current_then_stmt = current_then_stmt->next;
            }
        }
        printf("    jmp %s\n", end_if_label); // then_body 실행 후 endif_label로 점프

        // else_body (있을 경우)
        if (s->u.if_stmt.else_body) {
            printf("%s:\n", else_label); // else_label 정의
            Stmt *current_else_stmt = s->u.if_stmt.else_body->head;
            while (current_else_stmt) {
                gen_stmt(current_else_stmt, vars, var_count, func_name);
                current_else_stmt = current_else_stmt->next;
            }
        }
        printf("%s:\n", end_if_label); // endif_label 정의
        break;
    }
    case STMT_WHILE: {
        static int while_count = 0;
        int current_while_id = while_count++;
        char loop_label[64], end_loop_label[64];
        snprintf(loop_label, sizeof(loop_label), ".L_loop_%d", current_while_id);
        snprintf(end_loop_label, sizeof(end_loop_label), ".L_endloop_%d", current_while_id);

        printf("%s:\n", loop_label); // 루프 시작 레이블

        gen_expr(s->u.while_stmt.cond, vars, var_count); // 조건 평가, 결과는 eax에
        printf("    cmpl $0, %%eax\n"); // eax가 0이면 거짓
        printf("    je %s\n", end_loop_label); // 거짓이면 루프 종료 레이블로 점프

        // 루프 본문
        if (s->u.while_stmt.body) {
            Stmt *current_body_stmt = s->u.while_stmt.body->head;
            while (current_body_stmt) {
                gen_stmt(current_body_stmt, vars, var_count, func_name);
                current_body_stmt = current_body_stmt->next;
            }
        }
        printf("    jmp %s\n", loop_label); // 본문 실행 후 루프 시작으로 다시 점프

        printf("%s:\n", end_loop_label); // 루프 종료 레이블
        break;
    }
    case STMT_FOR: {
        static int for_count = 0;
        int current_for_id = for_count++;
        char loop_label[64], end_loop_label[64], increment_label[64];
        snprintf(loop_label, sizeof(loop_label), ".L_for_loop_%d", current_for_id);
        snprintf(end_loop_label, sizeof(end_loop_label), ".L_for_endloop_%d", current_for_id);
        snprintf(increment_label, sizeof(increment_label), ".L_for_increment_%d", current_for_id); // New label for increment

        // 1. Initialization (init)
        if (s->u.for_stmt.init) {
            gen_stmt(s->u.for_stmt.init, vars, var_count, func_name);
        }

        printf("%s:\n", loop_label); // Loop condition check label

        // 2. Condition (cond)
        if (s->u.for_stmt.cond) {
            gen_expr(s->u.for_stmt.cond, vars, var_count); // Evaluate condition, result in eax
            printf("    cmpl $0, %%eax\n"); // Compare eax with 0 (false)
            printf("    je %s\n", end_loop_label); // If false, jump to end of loop
        }

        // 3. Loop Body
        if (s->u.for_stmt.body) {
            Stmt *current_body_stmt = s->u.for_stmt.body->head;
            while (current_body_stmt) {
                gen_stmt(current_body_stmt, vars, var_count, func_name);
                current_body_stmt = current_body_stmt->next;
            }
        }

        // 4. Increment (increment)
        printf("%s:\n", increment_label); // Label for increment
        if (s->u.for_stmt.increment) {
            gen_expr(s->u.for_stmt.increment, vars, var_count); // Evaluate increment expression
        }

        printf("    jmp %s\n", loop_label); // Jump back to loop condition check

        printf("%s:\n", end_loop_label); // End of loop label
        break;
    }
    default:
        printf("    # unknown stmt kind\n");
        break;
    }
}

static void gen_function(Function *f) {
    Var vars[128];
    int var_count = 0;
    int stack_size = 0;

    alloc_locals_and_params(f, vars, &var_count, &stack_size);

    int is_main = (strcmp(f->name, "main") == 0);

    if (is_main) {
        printf("    .globl _main\n");
        printf("_main:\n");
    } else {
        printf("    .globl _%s\n", f->name);
        printf("_%s:\n", f->name);
    }

    printf("    pushl %%ebp\n");
    printf("    movl %%esp, %%ebp\n");
    if (stack_size > 0) {
        printf("    subl $%d, %%esp\n", stack_size);
    }

    char end_label[64];
    snprintf(end_label, sizeof(end_label), ".Lend_%s", f->name);

    if (f->body) {
        Stmt *s = f->body->head;
        while (s) {
            gen_stmt(s, vars, var_count, f->name); // func_name 전달
            s = s->next;
        }
    }

    printf("%s:\n", end_label);

    if (is_main && !has_return_stmt(f->body)) {
        printf("    movl $0, %%eax\n");
    }
    printf("    leave\n");
    printf("    ret\n\n");
}

// 함수 몸체에 return 문이 있는지 확인하는 헬퍼 함수
static int has_return_stmt(StmtList *body) {
    if (!body) return 0;
    Stmt *s = body->head;
    while (s) {
        if (s->kind == STMT_RETURN) return 1;
        if (s->kind == STMT_IF) {
            if (has_return_stmt(s->u.if_stmt.then_body)) return 1;
            if (has_return_stmt(s->u.if_stmt.else_body)) return 1;
        }
        if (s->kind == STMT_WHILE) {
            if (has_return_stmt(s->u.while_stmt.body)) return 1;
        }
        if (s->kind == STMT_FOR) {
            if (has_return_stmt(s->u.for_stmt.body)) return 1;
        }
        s = s->next;
    }
    return 0;
}

void gen_x86_program(FunctionList *prog) {
    if (!prog) {
        fprintf(stderr, "No program.\n");
        return;
    }

    printf("    .text\n");

    Function *f = prog->head;
    while (f) {
        gen_function(f);
        f = f->next;
    }
}