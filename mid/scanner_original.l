%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

int yycolumn = 0;
%}

%option noyywrap yylineno nodefault
%x COMMENT

%%

[ \t\r]+                { yycolumn += yyleng; }    /* 공백 무시 */
\n                      { yycolumn = 0; }          /* 줄바꿈 시 열 0으로 */

"//"[^\n]*              { /* 한 줄 주석 */ }

"/*"                    { BEGIN(COMMENT); }
<COMMENT>[^*\n]+        { /* 내부 텍스트 버리기 */ }
<COMMENT>"*"+[^*/\n]*   { /* 별 무리 뒤 다른문자들 */ }
<COMMENT>"*"+"/"        { BEGIN(INITIAL); }        /* 블록 주석 종료 */
<COMMENT>\n             { /* 줄바꿈만 처리 */ }

";"                     { yycolumn += yyleng; return ';'; }
"("                     { yycolumn += yyleng; return '('; }
")"                     { yycolumn += yyleng; return ')'; }
"+"                     { yycolumn += yyleng; return '+'; }
"-"                     { yycolumn += yyleng; return '-'; }
"*"                     { yycolumn += yyleng; return '*'; }
"/"                     { yycolumn += yyleng; return '/'; }

([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][+-]?[0-9]+)?  {
  yylval.num = strtod(yytext, NULL);
  yycolumn += yyleng;
  return NUMBER;
}

.                        {
  fprintf(stderr, "[lex] 알 수 없는 문자 '%s' (line %d, col %d)\n",
          yytext, yylineno, yycolumn+1);
  yycolumn += yyleng;
  return *yytext; /* 그대로 넘겨 파서에서 오류 유도 */
}

%%