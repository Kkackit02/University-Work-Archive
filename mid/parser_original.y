%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%locations

%union {
  double num;
}

%token <num> NUMBER

%right UPLUS UMINUS
%left '+' '-'
%left '*' '/'

%type <num> expr term factor

%define parse.error detailed

%%

input
  : %empty        /* <-- bison의 empty rule 경고 제거 */
  | input line
  ;

line
  : expr ';'        { printf("= %.10g\n", $1); fflush(stdout); }
  | error ';'       { yyerrok; }
  ;

expr
  : expr '+' term   { $$ = $1 + $3; }
  | expr '-' term   { $$ = $1 - $3; }
  | term
  ;

term
  : term '*' factor { $$ = $1 * $3; }
  | term '/' factor {
        $$ = $1 / $3;
    }
  | factor
  ;

factor
  : NUMBER          { $$ = $1; }
  | '(' expr ')'    { $$ = $2; }
  | '+' factor  %prec UPLUS  { $$ = +$2; }
  | '-' factor  %prec UMINUS { $$ = -$2; }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "[parse] error");
}

int main(void) {
  return yyparse();
}
