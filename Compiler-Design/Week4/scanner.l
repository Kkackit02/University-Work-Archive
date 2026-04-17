%option noyywrap

%{
#include <stdio.h>
%}

%%

\/\/.* {printf("Comment: %s\n", yytext);}
\/\*([^*]|\*+[^\/])*\*\/ {printf("Comment: %s\n", yytext);}
[0-9]+              { printf("NUMBER: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*   { printf("WORD: %s\n", yytext); }
[ \t\n]+            ;   /* 공백/개행 무시 */
.                   { printf("UNKNOWN: %s\n", yytext); }

%%

int main(void) {
    yylex();
    return 0;
}
