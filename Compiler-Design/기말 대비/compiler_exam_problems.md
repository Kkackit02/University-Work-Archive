# 컴파일러 기말고사 예상 문제집

이 예상 문제집은 제공된 컴파일러 코드베이스(`D:\Git\ComplierInKonkuk`)와 `compiler_study_guide.md` 내용을 기반으로 작성되었습니다. 각 문제 유형은 개념 이해, 코드 분석, 구현 방식 질문 등을 포함합니다.

---

## 1. 컴파일러 개요 및 기본 개념

1. 컴파일러의 주요 6단계(어휘 분석, 구문 분석, 의미 분석, 중간 코드 생성, 코드 최적화, 코드 생성)를 나열하고 각 단계의 입력과 출력을 설명하시오.
2. 이 프로젝트에서 `compiler_class-main` 디렉토리와 `wk` 디렉토리들이 존재하는 방식이 컴파일러 학습에 어떤 이점을 제공한다고 생각하는가?

---

## 2. 어휘 분석 (Lexical Analysis - Flex)

1. `Assignment_My_Compiler/parser/lexer.l` 파일에서 `%option noyywrap`의 역할은 무엇이며, 이것이 컴파일러 동작에 어떤 영향을 미치는지 설명하시오.
2. 다음 Flex 규칙의 동작을 설명하고, `yylval`이 어떻게 사용되는지 설명하시오.
    ```flex
    [0-9]+                  { yylval.int_value = atoi(yytext); return NUMBER; }
    [a-zA-Z_][a-zA-Z0-9_]*  { yylval.ident = strdup(yytext); return IDENT; }
    ```
3. Flex에서 정규 표현식 `[ 	
]+`와 `"//".*`가 각각 어떤 역할을 하며, 이러한 규칙이 컴파일러의 효율성에 어떤 기여를 하는가?
4. 만약 `lexer.l` 파일에 알 수 없는 문자(`Unknown character`)를 처리하는 규칙이 없다면 어떤 문제가 발생할 수 있으며, 이를 어떻게 해결할 수 있는가?

---

## 3. 구문 분석 (Syntax Analysis - Bison)

1. `Assignment_My_Compiler/parser/parser.y` 파일에서 `%union` 지시어의 필요성과, `yylval.int_value`와 `yylval.ident`처럼 멤버를 직접 참조하는 이유를 설명하시오.
2. Bison에서 다음 연산자 우선순위 및 결합성 정의가 문법 분석에 어떤 영향을 미치는지 설명하시오.
    ```bison
    %right '='
    %left EQ NE
    %left LT GT LE GE
    %left '+' '-'
    %left '*' '/'
    ```
3. `parser.y` 파일에서 `expr : expr '+' expr { $$ = new_binop_expr(BIN_ADD, $1, $3); }`와 같은 규칙이 AST를 생성하는 원리를 설명하시오. 특히 `$$`, `$1`, `$3`의 의미를 명확히 하시오.
4. Bison 파서가 Shift-Reduce 충돌을 감지했을 때, 이를 해결하기 위한 일반적인 방법 두 가지를 제시하고 설명하시오.
5. `yyerror(const char *s)` 함수의 역할은 무엇이며, 파싱 오류가 발생했을 때 이 함수가 어떻게 호출되는지 설명하시오.

---

## 4. 추상 구문 트리 (Abstract Syntax Tree - AST)

1. AST는 파스 트리와 어떻게 다르며, 컴파일러의 후반 단계에서 AST를 사용하는 주된 이점은 무엇인가?
2. `Assignment_My_Compiler/include/ast.h` 파일의 `struct Expr`와 `struct Stmt`에서 `union`을 사용하는 이유는 무엇이며, `ExprKind`나 `StmtKind`와 같은 `enum` 타입과 함께 어떻게 활용되는지 설명하시오.
3. `Assignment_My_Compiler/src/ast.c`에서 `new_int_expr`, `new_binop_expr`, `new_if_stmt`와 같은 함수들이 AST 노드를 생성하는 과정을 설명하시오. 특히 메모리 할당(예: `calloc`)과 문자열 복사(예: `strdup_s`)의 중요성을 강조하시오.
4. 다음 C 코드가 주어졌을 때, 해당 코드에 대한 AST의 일부를 간략하게 그려보거나 텍스트로 표현하시오.
    ```c
    int main() {
        int x = 10;
        if (x > 5) {
            return x + 1;
        } else {
            return 0;
        }
    }
    ```
    (함수 `main`과 `vardecl`, `if_stmt` 부분에 초점)

---

## 5. 의미 분석 (Semantic Analysis)

1. 심볼 테이블의 주된 역할은 무엇이며, 이 프로젝트의 `symbol_table.c`에서 스코프(Scope)를 관리하기 위해 "가드 노드(guard node)"를 사용하는 방법을 설명하시오. `scope_push()`와 `scope_pop()`의 동작 원리를 포함하시오.
2. `9wk/minic_type/sema.c` 파일에서 `check_expr()` 함수가 변수의 타입을 추론하고 미선언 변수 사용 오류를 감지하는 과정을 설명하시오. 관련 심볼 테이블 함수(예: `sym_get`)의 역할도 포함하시오.
3. 다음 코드에서 `binop_type` 함수(`sema.c` 참고)에 따라 `c` 변수의 최종 타입은 무엇이며, 그 이유는 무엇인가?
    ```c
    int a = 10;
    float b = 2.5;
    /* ... */
    TypeKind type_of_c = binop_type(a의_타입, b의_타입);
    ```
4. 함수 정의 시 `handle_func_def` (sema.c 참고) 함수가 심볼 테이블을 어떻게 활용하여 함수의 중복 정의를 방지하고 매개변수 정보를 등록하는지 설명하시오.
5. 타입 검사에서 "Narrowing Conversion"은 무엇이며, `sema.c`의 `handle_decl` 또는 `check_expr` 함수에서 이를 어떻게 감지하고 처리하는지 설명하시오.

---

## 6. 중간 코드 생성 (Intermediate Code Generation - IR)

1. 중간 코드(IR)를 사용하는 주된 이유 두 가지를 설명하고, 이 프로젝트에서 사용된 3-주소 코드(Three-Address Code, TAC)의 일반적인 형태와 장점을 설명하시오.
2. `10wk/minic_ir/include/ir.h`에 정의된 `IR` 구조체와 `IROp` 열거형이 3-주소 코드를 어떻게 표현하는지 설명하시오.
3. `10wk/minic_ir/src/codegen.c`의 `gen` 함수에서 `new_temp()` 함수는 어떤 역할을 하며, 이 함수가 생성하는 임시 변수는 코드 생성 과정에서 어떻게 사용되는가?
4. 다음 AST 표현식에 대해 `10wk/minic_ir/src/codegen.c`의 `gen` 함수가 생성할 수 있는 IR 시퀀스를 작성하시오. (가상의 `t0`, `t1` 등을 사용)
    `x = 10 + y * 5;` (여기서 `x`, `y`는 변수라고 가정)

---

## 7. 코드 생성 (Code Generation - x86 Assembly)

1. `Assignment_My_Compiler/src/codegen_x86.c`에서 함수 프롤로그(`pushl %ebp`, `movl %esp, %ebp`, `subl $size, %esp`)와 에필로그(`leave`, `ret`)의 역할은 무엇이며, 스택 프레임 설정 및 해제 과정을 설명하시오.
2. x86 어셈블리에서 지역 변수와 함수 매개변수는 `ebp` 레지스터를 기준으로 어떻게 접근되는지 설명하시오. (`alloc_locals_and_params` 함수 참고)
3. `codegen_x86.c`의 `gen_binop` 함수에서 이항 연산(`+`, `-`, `*`, `/`)과 비교 연산(`==`, `!=`, `<`, `>`)이 각각 x86 어셈블리 명령어로 어떻게 변환되는지 예시를 들어 설명하시오. 특히 비교 연산의 경우, 결과 값이 `eax`에 어떻게 설정되는지 명확히 하시오.
4. C 호출 규약(cdecl)에 따라 함수 `foo(a, b)`를 호출하는 `gen_call` 함수(codegen_x86.c)의 동작을 어셈블리 코드와 함께 설명하시오. 인자 전달 및 스택 정리는 누가 담당하는가?
5. `codegen_x86.c`의 `gen_stmt` 함수에서 `if` 문(`STMT_IF`)과 `while` 문(`STMT_WHILE`)과 같은 제어 흐름 문장이 x86 어셈블리 레이블(`L_else_X`, `L_endloop_X`)과 조건부/무조건부 점프 명령(예: `je`, `jmp`)을 사용하여 어떻게 구현되는지 설명하시오.

---

## 8. 전체 컴파일러 통합 및 테스트

1. `Assignment_My_Compiler/src/main.c` 파일이 컴파일러의 각 단계(어휘 분석, 구문 분석, 코드 생성)를 어떻게 통합하여 소스 코드로부터 어셈블리 파일을 생성하는지 전체 흐름을 설명하시오.
2. `Assignment_My_Compiler/test/` 디렉토리의 역할은 무엇이며, 이 디렉토리에 있는 테스트 파일을 활용하여 컴파일러의 특정 기능(예: `for` 루프 처리)이 올바르게 구현되었는지 어떻게 확인할 수 있는가?

---
힌트: 각 문제에 답변할 때는 `compiler_study_guide.md`의 해당 섹션을 참조하고, 가능하면 실제 코드베이스의 파일명과 함수명을 인용하여 답변하면 좋습니다.