%option noyywrap

%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

ID      [A-Za-z_][A-Za-z0-9_]*
NUM     [0-9]+(\.[0-9]*)?|\.[0-9]+
WS      [ \t\r]+

%%

"show"      { return T_SHOW; }
{ID}        { yylval.sval = strdup(yytext); return T_ID; }

{NUM}       { yylval.dval = atof(yytext);   return T_NUMBER; }

"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"="         { return '='; }
"("         { return '('; }
")"         { return ')'; }
";"         { return T_EOL; }

"//"[^\n]*  { /* skip */ }

{WS}        { /* skip */ }
\n          { return '\n'; }

.           { fprintf(stderr, "unknown char: %s\n", yytext); }

%%
