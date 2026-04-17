#ifndef AST_H
#define AST_H

typedef struct Expr Expr;
typedef struct ExprList ExprList;
typedef struct Stmt Stmt;
typedef struct StmtList StmtList;
typedef struct Param Param;
typedef struct ParamList ParamList;
typedef struct Function Function;
typedef struct FunctionList FunctionList;

typedef enum {
    EXPR_INT,
    EXPR_VAR,
    EXPR_BINOP,
    EXPR_CALL,
    EXPR_ASSIGN
} ExprKind;

typedef enum {
    BIN_ADD,
    BIN_SUB,
    BIN_MUL,
    BIN_DIV,
    BIN_EQ,  /* == */
    BIN_NE,  /* != */
    BIN_LT,  /* < */
    BIN_GT,  /* > */
    BIN_LE,  /* <= */
    BIN_GE   /* >= */
} BinOpKind;

struct Expr {
    ExprKind kind;
    union {
        int int_value;
        char *var_name;
        struct {
            BinOpKind op;
            Expr *lhs;
            Expr *rhs;
        } binop;
        struct {
            char *func_name;
            ExprList *args;
        } call;
        struct {
            char *var_name;
            Expr *value;
        } assign_expr;
    } u;
};

struct ExprList {
    Expr *expr;
    ExprList *next;
};

typedef enum {
    STMT_EXPR,
    STMT_RETURN,
    STMT_VARDECL,
    STMT_ASSIGN,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR
} StmtKind;

struct Stmt {
    StmtKind kind;
    union {
        Expr *expr; /* expr stmt, return stmt */
        struct {
            char *var_name;
            Expr *initial_value; /* NULL if no initialization */
        } vardecl;
        struct {
            char *var_name;
            Expr *value;
        } assign;
        struct {
            Expr *cond;
            StmtList *then_body;
            StmtList *else_body; /* NULL if no else */
        } if_stmt;
        struct {
            Expr *cond;
            StmtList *body;
        } while_stmt;
        struct {
            Stmt *init; /* Can be vardecl or expr stmt */
            Expr *cond;
            Expr *increment;
            StmtList *body;
        } for_stmt;
    } u;
    Stmt *next;
};

struct StmtList {
    Stmt *head;
    Stmt *tail;
};

struct Param {
    char *name;
    Param *next;
};

struct ParamList {
    Param *head;
    Param *tail;
};

struct Function {
    char *name;
    ParamList *params;
    StmtList *body;
    Function *next;
};

struct FunctionList {
    Function *head;
    Function *tail;
};

Expr *new_int_expr(int value);
Expr *new_var_expr(const char *name);
Expr *new_binop_expr(BinOpKind op, Expr *lhs, Expr *rhs);
Expr *new_call_expr(const char *func_name, ExprList *args);
Expr *new_assign_expr(const char *name, Expr *value);

ExprList *expr_list_append(ExprList *list, Expr *expr);

Stmt *new_expr_stmt(Expr *e);
Stmt *new_return_stmt(Expr *e);
Stmt *new_vardecl_stmt(const char *name, Expr *initial_value);
Stmt *new_assign_stmt(const char *name, Expr *value);
Stmt *new_if_stmt(Expr *cond, StmtList *then_body, StmtList *else_body);
Stmt *new_while_stmt(Expr *cond, StmtList *body);
Stmt *new_for_stmt(Stmt *init, Expr *cond, Expr *increment, StmtList *body);

StmtList *stmt_list_append(StmtList *list, Stmt *stmt);

ParamList *param_list_append(ParamList *list, const char *name);

Function *new_function(const char *name, ParamList *params, StmtList *body);
FunctionList *function_list_append(FunctionList *list, Function *func);

/* global root */
extern FunctionList *g_program;

#endif
