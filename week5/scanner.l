%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>

void yyerror(const char*);
%}

%option noyywrap

/* Pattern definitions */
ID      [a-zA-Z_][a-zA-Z0-9_]*
NUM     [0-9]+

%%

"print"         { return T_PRINT; }
{ID}            { yylval.sval = strdup(yytext); return T_ID; }
{NUM}           { yylval.dval = atof(yytext); return T_NUMBER; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"="             { return '='; }
"("             { return '('; }
")"             { return ')'; }

[ \t\r]+        { /* skip whitespace */ }
"//"[^\n]*     { /* skip comments */ }
\n             { return '\n'; }

.               { yyerror("unknown character"); }

%%

