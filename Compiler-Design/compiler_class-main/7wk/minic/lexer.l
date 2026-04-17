%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Token {
  T_INT, T_FLOAT, T_IF, T_ELSE, T_WHILE, T_RETURN,
  T_ID, T_NUM_INT, T_NUM_FLOAT,
  T_PLUS, T_MINUS, T_MUL, T_DIV,
  T_ASSIGN, T_EQ, T_NE, T_LT, T_LE, T_GT, T_GE,
  T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE, T_SEMI,
  T_UNKNOWN
};

char *token_name(enum Token t) {
  switch(t) {
    case T_INT: return "INT";
    case T_FLOAT: return "FLOAT";
    case T_IF: return "IF";
    case T_ELSE: return "ELSE";
    case T_WHILE: return "WHILE";
    case T_RETURN: return "RETURN";
    case T_ID: return "ID";
    case T_NUM_INT: return "NUM_INT";
    case T_NUM_FLOAT: return "NUM_FLOAT";
    case T_PLUS: return "PLUS";
    case T_MINUS: return "MINUS";
    case T_MUL: return "MUL";
    case T_DIV: return "DIV";
    case T_ASSIGN: return "ASSIGN";
    case T_EQ: return "EQ";
    case T_NE: return "NE";
    case T_LT: return "LT";
    case T_LE: return "LE";
    case T_GT: return "GT";
    case T_GE: return "GE";
    case T_LPAREN: return "LPAREN";
    case T_RPAREN: return "RPAREN";
    case T_LBRACE: return "LBRACE";
    case T_RBRACE: return "RBRACE";
    case T_SEMI: return "SEMI";
    default: return "UNKNOWN";
  }
}
%}

%option noyywrap nodefault

ID      [a-zA-Z_][a-zA-Z0-9_]*
FNUM    ([0-9]*\.[0-9]+)
INUM    ([0-9]+)
WS      [ \t\r\n]+

%%

{WS}            ;     /* ignore whitespace */
"//".*          ;     /* line comment */
"/*"([^*]|\*+[^*/])*\*+ "/"   ; /* block comment */

"int"           { printf("T_INT\n"); }
"float"         { printf("T_FLOAT\n"); }
"if"            { printf("T_IF\n"); }
"else"          { printf("T_ELSE\n"); }
"while"         { printf("T_WHILE\n"); }
"return"        { printf("T_RETURN\n"); }

{FNUM}          { printf("T_NUM_FLOAT(%s)\n", yytext); }
{INUM}          { printf("T_NUM_INT(%s)\n", yytext); }
{ID}            { printf("T_ID(%s)\n", yytext); }

"=="            { printf("T_EQ\n"); }
"!="            { printf("T_NE\n"); }
"<="            { printf("T_LE\n"); }
">="            { printf("T_GE\n"); }
"<"             { printf("T_LT\n"); }
">"             { printf("T_GT\n"); }

"="             { printf("T_ASSIGN\n"); }
"+"             { printf("T_PLUS\n"); }
"-"             { printf("T_MINUS\n"); }
"*"             { printf("T_MUL\n"); }
"/"             { printf("T_DIV\n"); }

"("             { printf("T_LPAREN\n"); }
")"             { printf("T_RPAREN\n"); }
"{"             { printf("T_LBRACE\n"); }
"}"             { printf("T_RBRACE\n"); }
";"             { printf("T_SEMI\n"); }

.               { printf("T_UNKNOWN(%s)\n", yytext); }

%%
int main(void) {
  yylex();
  return 0;
}
