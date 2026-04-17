%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int int_value;
    char *ident;
    Expr *expr;
    ExprList *expr_list;
    Stmt *stmt;
    StmtList *stmt_list;
    ParamList *param_list;
    Function *function;
    FunctionList *function_list;
}

%token INT RETURN IF ELSE WHILE FOR
%token <int_value> NUMBER
%token <ident> IDENT
%token EQ NE LT GT LE GE

%type <expr> expr primary
%type <expr_list> arg_list arg_list_opt
%type <stmt> stmt vardecl if_stmt while_stmt for_stmt
%type <stmt> for_init_opt
%type <expr> for_cond_opt for_increment_opt
%type <stmt_list> stmt_list stmt_list_opt compound_stmt
%type <param_list> param_list param_list_opt
%type <function> function
%type <function_list> func_list program

%right '='
%left EQ NE
%left LT GT LE GE
%left '+' '-'
%left '*' '/'

%%

program
    : func_list                { g_program = $$; }
    ;

func_list
    : func_list function       { $$ = function_list_append($1, $2); }
    | function                 { $$ = function_list_append(NULL, $1); }
    ;

function
    : INT IDENT '(' param_list_opt ')' compound_stmt
                              { $$ = new_function($2, $4, $6); }
    ;

param_list_opt
    : /* empty */              { $$ = NULL; }
    | param_list               { $$ = $1; }
    ;

/* C 스타일: int a, int b, ... */
param_list
    : INT IDENT                    { $$ = param_list_append(NULL, $2); }
    | param_list ',' INT IDENT     { $$ = param_list_append($1, $4); }
    ;

compound_stmt
    : '{' stmt_list_opt '}'    { $$ = $2; }
    ;

stmt_list_opt
    : /* empty */              { $$ = NULL; }
    | stmt_list                { $$ = $1; }
    ;

stmt_list
    : stmt_list stmt           { $$ = stmt_list_append($1, $2); }
    | stmt                     { $$ = stmt_list_append(NULL, $1); }
    ;

stmt
    : vardecl ';'              { $$ = $1; }
    | RETURN expr ';'          { $$ = new_return_stmt($2); }
    | expr ';'                 { $$ = new_expr_stmt($1); }
    | if_stmt                  { $$ = $1; }
    | while_stmt               { $$ = $1; }
    | for_stmt                 { $$ = $1; }
    ;

if_stmt
    : IF '(' expr ')' compound_stmt                 { $$ = new_if_stmt($3, $5, NULL); }
    | IF '(' expr ')' compound_stmt ELSE compound_stmt { $$ = new_if_stmt($3, $5, $7); }
    ;

while_stmt
    : WHILE '(' expr ')' compound_stmt              { $$ = new_while_stmt($3, $5); }

for_stmt
    : FOR '(' for_init_opt ';' for_cond_opt ';' for_increment_opt ')' compound_stmt
                              { $$ = new_for_stmt($3, $5, $7, $9); }
    ;

for_init_opt
    : /* empty */              { $$ = NULL; }
    | INT IDENT                { $$ = new_vardecl_stmt($2, NULL); }
    | INT IDENT '=' expr       { $$ = new_vardecl_stmt($2, $4); }
    | expr                     { $$ = new_expr_stmt($1); }

for_cond_opt
    : /* empty */              { $$ = NULL; }
    | expr                     { $$ = $1; }

for_increment_opt
    : /* empty */              { $$ = NULL; }
    | expr                     { $$ = $1; }

vardecl
    : INT IDENT                { $$ = new_vardecl_stmt($2, NULL); }
    | INT IDENT '=' expr       { $$ = new_vardecl_stmt($2, $4); }
    ;

expr
    : expr '+' expr            { $$ = new_binop_expr(BIN_ADD, $1, $3); }
    | expr '-' expr            { $$ = new_binop_expr(BIN_SUB, $1, $3); }
    | expr '*' expr            { $$ = new_binop_expr(BIN_MUL, $1, $3); }
    | expr '/' expr            { $$ = new_binop_expr(BIN_DIV, $1, $3); }
    | expr EQ expr             { $$ = new_binop_expr(BIN_EQ, $1, $3); }
    | expr NE expr             { $$ = new_binop_expr(BIN_NE, $1, $3); }
    | expr LT expr             { $$ = new_binop_expr(BIN_LT, $1, $3); }
    | expr GT expr             { $$ = new_binop_expr(BIN_GT, $1, $3); }
    | expr LE expr             { $$ = new_binop_expr(BIN_LE, $1, $3); }
    | expr GE expr             { $$ = new_binop_expr(BIN_GE, $1, $3); }
    | IDENT '=' expr           { $$ = new_assign_expr($1, $3); }
    | primary                  { $$ = $1; }
    ;

primary
    : NUMBER                   { $$ = new_int_expr($1); }
    | IDENT                    { $$ = new_var_expr($1); }
    | IDENT '(' arg_list_opt ')' { $$ = new_call_expr($1, $3); }
    | '(' expr ')'             { $$ = $2; }
    ;

arg_list_opt
    : /* empty */              { $$ = NULL; }
    | arg_list                 { $$ = $1; }
    ;

arg_list
    : expr                     { $$ = expr_list_append(NULL, $1); }
    | arg_list ',' expr        { $$ = expr_list_append($1, $3); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "parse error: %s\n", s);
}
