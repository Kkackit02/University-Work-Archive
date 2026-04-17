%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lexer / error */
int yylex(void);
void yyerror(const char *s);

/* --- 심볼테이블(아주 단순) --- */
typedef struct Sym {
  char *name;
  int   value;
  struct Sym *next;
} Sym;
static Sym *symtab = NULL;

static Sym* lookup(const char *name){
  for (Sym *p = symtab; p; p = p->next)
    if (strcmp(p->name, name) == 0) return p;
  return NULL;
}
static int getval(const char *name){
  Sym *s = lookup(name);
  if (!s) {
    fprintf(stderr, "undefined variable: %s\n", name);
    return 0;
  }
  return s->value;
}
static void setval(const char *name, int v){
  Sym *s = lookup(name);
  if (!s) {
    s = (Sym*)malloc(sizeof(Sym));
    s->name = strdup(name);
    s->next = symtab;
    symtab = s;
  }
  s->value = v;
}
%}

/* --- 토큰/타입 --- */
%union { int ival; char *sval; }

%token <ival> T_NUMBER
%token <sval> T_ID
%token        T_PRINT

%left '+' '-'
%left '*' '/' '%'
%right UMINUS

%type <ival> expr stmt
%start input

%%

/* 줄 단위로 즉시 reduce → 출력 */
input
  : /* empty */
  | input line
  ;

line
  : stmt '\n'              { printf("%d\n", $1); }
  | '\n'                   { /* 빈 줄 무시 */ }
  | error '\n'             { yyerrok; /* 에러 줄 스킵 */ }
  ;

stmt
  : expr                   { $$ = $1; }
  | T_ID '=' expr          { setval($1, $3); $$ = $3; free($1); }
  | T_PRINT expr           { $$ = $2; }  /* print도 값 출력(line에서 일괄 출력) */
  ;

expr
  : expr '+' expr          { $$ = $1 + $3; }
  | expr '-' expr          { $$ = $1 - $3; }
  | expr '*' expr          { $$ = $1 * $3; }
  | expr '%' expr          { if ($3 == 0) { yyerror("mod by zero");       $$ = 0; } else $$ = $1 % $3; }
  | '-' expr %prec UMINUS  { $$ = -$2; }
  | '(' expr ')'           { $$ = $2; }
  | T_NUMBER               { $$ = $1; }
  | T_ID                   { $$ = getval($1); free($1); }
  ;

%%

void yyerror(const char *s){ fprintf(stderr, "parse error: %s\n", s); }

int main(void){
  return yyparse();
}
