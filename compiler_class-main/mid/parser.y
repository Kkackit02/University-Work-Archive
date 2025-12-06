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

/* (선택) 에러 메시지 자세히 */
%define parse.error detailed

%%

input
  : %empty        /* <-- bison의 empty rule 경고 제거 */
  | input line
  ;

line
  : expr ';'          { printf("= %.10g\n", $1); fflush(stdout); }
  | ';'               { fprintf(stderr, "[parse] 빈 식입니다 (line %d, col %d)\n",
                                @$.first_line, @$.first_column); }
  | error ';'         { yyerrok; }
  /* 여는 괄호 없이 ')' 가 등장한 경우: 결과는 그대로 출력하되 경고 */
  | expr ')' ';'      {
                        fprintf(stderr,
                                "[parse] 여는 괄호 없이 닫는 괄호가 있습니다 (line %d, col %d)\n",
                                @2.first_line, @2.first_column);
                        printf("= %.10g\n", $1); fflush(stdout);
                      }

expr
  : expr '+' term   { $$ = $1 + $3; }
  | expr '-' term   { $$ = $1 - $3; }
  | term
  ;

term
  : term '*' factor { $$ = $1 * $3; }
  | term '/' factor {
      if ($3 == 0.0) {
        fprintf(stderr, "[sem] 0으로 나눌 수 없습니다\n");
        $$ = 0.0;
      } else {
        $$ = $1 / $3;
      }
    }
  | factor
  ;

factor
  : NUMBER            { $$ = $1; }
  | '(' expr ')'      { $$ = $2; }
  | '+' factor %prec UPLUS  { $$ = +$2; }
  | '-' factor %prec UMINUS { $$ = -$2; }
  /* 닫는 괄호 누락: '(' expr 다음 예상되는 ')'가 없음 */
  | '(' expr error    {
        fprintf(stderr,
                "[parse] 닫는 괄호 ')'가 누락되었습니다 (line %d, col %d 부근)\n",
                @2.last_line, @2.last_column + 1);
        /* 에러 복구: 안의 값으로 계속 진행 */
        yyerrok;
        $$ = $2;
    }
  ;
%%

void yyerror(const char *s) {
  fprintf(stderr, "[parse] error");
}

int main(void) {
  return yyparse();
}
