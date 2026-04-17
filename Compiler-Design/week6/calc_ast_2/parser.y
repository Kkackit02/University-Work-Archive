%{
#include <stdio.h>
#include "ast.h"
int yylex(void);
void yyerror(const char *s);
AST *root;
%}

%code requires {  /* parser.tab.h에도 AST 타입 포함 */
  #include "ast.h"
}

%union {
    double num;
    AST *node;
}

%token <num> NUMBER
%type  <node> expr term factor

%right UPLUS UMINUS
%left '+' '-'
%left '*' '/'

%start input

%%

/* 여러 줄을 EOF까지 파싱 */
input
  : /* empty */
  | input line
  ;

line
  : expr ';'      { printf("= %.10g\n", $1); fflush(stdout); }
  | ';'           { fprintf(stderr, "[parse] 빈 식입니다 (line %d, col %d)\n", @$.first_line, @$.first_column); }
  | error ';'     { yyerrok; }
  /* 여는 괄호 없이 ')'가 등장한 경우: 결과는 그대로 출력하되 경고 */
  | expr ')' ';'  {
                    fprintf(stderr,
                      "[parse] 여는 괄호 없는 닫는 괄호가 있습니다 (line %d, col %d)\n",
                      @2.first_line, @2.first_column);
                    printf("= %.10g\n", $1); fflush(stdout);
                  }
  ;

/* 중위 표기 + 우선순위/결합규칙 */
expr
  : expr '+' term  { $$ = new_op(NODE_ADD, $1, $3); }
  | expr '-' term  { $$ = new_op(NODE_SUB, $1, $3); }
  | term
  ;

term
  : term '*' factor { $$ = new_op(NODE_MUL, $1, $3); }
  | term '/' factor { $$ = new_op(NODE_DIV, $1, $3); }
  | factor
  ;

factor
  : NUMBER                         { $$ = new_num($1); }
  | '(' expr ')'                   { $$ = $2; }
  | '-' factor   %prec UMINUS      { $$ = new_op(NODE_SUB, new_num(0), $2); }
  | '+' factor   %prec UPLUS       { $$ = $2; }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}