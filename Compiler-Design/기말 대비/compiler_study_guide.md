# 컴파일러 기말고사 대비 자료집

## 1. 컴파일러 개요

이 자료집은 `D:\Git\ComplierInKonkuk` 디렉토리에 있는 컴파일러 관련 코드베이스를 기반으로 작성되었습니다. 프로젝트는 주차별(`wk` 폴더)로 컴파일러의 다양한 단계를 점진적으로 구현하는 방식으로 구성되어 있으며, `Assignment_My_Compiler` 폴더는 최종 컴파일러 프로젝트로 보입니다.

컴파일러는 일반적으로 다음 단계를 거쳐 소스 코드를 실행 가능한 형태로 변환합니다:
1.  **어휘 분석 (Lexical Analysis)**: 소스 코드를 토큰 스트림으로 변환.
2.  **구문 분석 (Syntax Analysis)**: 토큰 스트림을 파스 트리 또는 추상 구문 트리(AST)로 변환.
3.  **의미 분석 (Semantic Analysis)**: 프로그램의 의미를 확인하고 타입 체크, 심볼 테이블 관리 등을 수행.
4.  **중간 코드 생성 (Intermediate Code Generation)**: AST를 기계 독립적인 중간 표현(IR)으로 변환.
5.  **코드 최적화 (Code Optimization)**: 중간 코드를 효율적으로 개선 (이 프로젝트에서는 크게 다루지 않을 수 있음).
6.  **코드 생성 (Code Generation)**: 중간 코드를 타겟 아키텍처(여기서는 x86 어셈블리)의 기계 코드로 변환.

## 2. 어휘 분석 (Lexical Analysis - Scanner)

*   **개념**: 소스 코드를 읽어 의미 있는 최소 단위인 '토큰(Token)'으로 분리하는 과정입니다. 정규 표현식(Regular Expression)을 사용하여 토큰 패턴을 정의합니다. Lexer (Scanner)는 소스 코드 문자 스트림을 입력으로 받아 토큰 스트림을 출력합니다.
*   **도구**: Flex (Fast Lexical Analyzer Generator) - `.l` 파일을 입력으로 받아 `lex.yy.c` 파일을 생성합니다.
*   **주요 파일**: `scanner.l` 또는 `lexer.l` (Flex 입력 파일), 생성된 `lex.yy.c`
    *   예시 경로: `Assignment_My_Compiler/parser/lexer.l`
*   **Flex 파일 구조 (`lexer.l` 예시 분석)**:

    ```flex
    %option noyywrap

    %{
    #include <stdlib.h>
    #include <string.h>
    #include "ast.h"         // AST 정의를 포함 (파서에서 AST 노드를 빌드하기 위해 필요할 수 있음)
    #include "parser.tab.h"   // Bison이 생성하는 토큰 정의 (NUMBER, IDENT, INT 등)
    %}

    %%
    [ \t\r\n]+              ; // 공백, 탭, 개행 문자는 무시
    "//".*                  ; // 한 줄 주석 무시

    // 키워드 (Keywords)
    "int"                   { return INT; }
    "return"                { return RETURN; }
    "if"                    { return IF; }
    "else"                  { return ELSE; }
    "while"                 { return WHILE; }
    "for"                   { return FOR; }

    // 숫자 리터럴 (Number Literals)
    [0-9]+                  { yylval.int_value = atoi(yytext); return NUMBER; }

    // 식별자 (Identifiers)
    [a-zA-Z_][a-zA-Z0-9_]*  { yylval.ident = strdup(yytext); return IDENT; }

    // 단일 문자 연산자 및 구분자 (Single-character Operators & Punctuators)
    "{"                     { return '{'; }
    "}"                     { return '}'; }
    "("                     { return '('; }
    ")"                     { return ')'; }
    ";"                     { return ';'; }
    ","                     { return ','; }
    "="                     { return '='; }
    "+"                     { return '+'; }
    "-"                     { return '-'; }
    "*"                     { return '*'; }
    "/"                     { return '/'; }

    // 다중 문자 연산자 (Multi-character Operators)
    "=="                    { return EQ; }
    "!="                    { return NE; }
    "<"                     { return LT; }
    ">"                     { return GT; }
    "<="                    { return LE; }
    ">="                    { return GE; }

    .                       { fprintf(stderr, "Unknown character: %s\n", yytext); } // 알 수 없는 문자 처리

    %%
    ```

*   **주요 요소 설명**:
    *   `%option noyywrap`: Flex는 기본적으로 입력의 끝에 도달하면 `yywrap()` 함수를 호출하여 더 많은 입력이 있는지 확인합니다. `noyywrap` 옵션은 이 동작을 비활성화하고, EOF(End-Of-File)에 도달하면 `yylex()`가 0을 반환하도록 합니다. 이는 단일 입력 파일만 처리할 때 유용합니다.
    *   `%{ ... %}` 블록: 이 블록 안의 내용은 생성된 `lex.yy.c` 파일의 최상단에 그대로 복사됩니다. 일반적으로 필요한 헤더 파일(`stdlib.h`, `string.h`, `ast.h`, `parser.tab.h`)을 포함하고 전역 변수나 함수 선언을 합니다.
        *   `"parser.tab.h"`: Bison이 파서 생성 시 함께 생성하는 헤더 파일입니다. 여기에 `%token`으로 선언된 모든 토큰들의 정수형 상수 정의가 포함되어 있습니다 (예: `#define INT 257`, `#define NUMBER 258` 등). Lexer는 이 정의를 사용하여 올바른 토큰 타입을 반환합니다.
    *   **정규 표현식 규칙**: `정규_표현식 { 액션 }` 형태로 정의됩니다.
        *   `[ \t\r\n]+ ;`: 하나 이상의 공백, 탭, 캐리지 리턴, 개행 문자를 만나면 아무것도 하지 않고 무시합니다. (세미콜론 `;`은 비어있는 액션을 의미)
        *   `"//".* ;`: `//`로 시작하는 한 줄 주석을 무시합니다.
        *   **키워드**: `"int" { return INT; }`와 같이 특정 문자열이 매치되면 해당 키워드에 해당하는 토큰 타입(Bison에서 정의된 `INT`)을 반환합니다.
        *   **숫자**: `[0-9]+ { yylval.int_value = atoi(yytext); return NUMBER; }`. 하나 이상의 숫자가 매치되면 `yytext` (매치된 문자열)를 `atoi()`로 정수형으로 변환하여 `yylval.int_value`에 저장합니다. 그리고 `NUMBER` 토큰 타입을 반환합니다.
        *   **식별자**: `[a-zA-Z_][a-zA-Z0-9_]* { yylval.ident = strdup(yytext); return IDENT; }`. 문자나 언더스코어로 시작하고, 문자, 숫자, 언더스코어가 이어지는 패턴이 매치되면 `yytext`를 `strdup()`로 복제하여 `yylval.ident`에 저장하고 `IDENT` 토큰 타입을 반환합니다. `strdup`를 사용하는 이유는 `yytext`가 전역 버퍼이며, 다음 `yylex` 호출 시 내용이 변경될 수 있기 때문입니다.
        *   **연산자/구분자**: `"+"` 같은 단일 문자나 `"=="` 같은 다중 문자 연산자가 매치되면 해당 토큰 타입(또는 ASCII 값)을 반환합니다.
        *   `. { fprintf(stderr, ...); }`: 어떤 규칙에도 매치되지 않는 문자를 만났을 때의 오류 처리입니다. 표준 오류 스트림에 메시지를 출력합니다.
    *   `yylval`: `yylval`은 Flex와 Bison 간에 값(semantic value)을 전달하는 데 사용되는 전역 변수입니다. Bison의 `%union` 선언에 따라 다양한 타입의 값을 담을 수 있습니다. 여기서는 `int_value` (숫자)와 `ident` (식별자 문자열)를 전달하는 데 사용됩니다.
*   **시험 대비**: Flex 문법 (`%option`, `%{ %}`, `%%`), 정규 표현식을 통한 토큰 정의 규칙, `yytext`, `yyleng`, `yylval`의 역할과 사용법, `return` 값을 통한 토큰 타입 전달, 주석 및 공백 처리, 오류 처리 방식.

다음은 **3. 구문 분석 (Syntax Analysis - Parser)** 섹션을 채울 차례입니다.
`Assignment_My_Compiler/parser/parser.y` 파일을 분석하여 Bison의 문법 규칙, AST 노드 생성 방법 등을 추가하겠습니다.


## 3. 구문 분석 (Syntax Analysis - Parser)

*   **개념**: 어휘 분석기가 생성한 토큰 스트림을 문법 규칙에 따라 분석하여 프로그램의 구조를 확인하고, 파스 트리(Parse Tree) 또는 추상 구문 트리(Abstract Syntax Tree, AST)를 생성합니다. Bison은 LALR(1) 파서를 생성합니다.
*   **도구**: Bison (GNU Parser Generator) - `.y` 파일을 입력으로 받아 `parser.tab.c` 및 `parser.tab.h` 파일을 생성합니다.
*   **주요 파일**: `parser.y` (Bison 입력 파일), 생성된 `parser.tab.c`, `parser.tab.h`
    *   예시 경로: `Assignment_My_Compiler/parser/parser.y`
*   **Bison 파일 구조 (`parser.y` 예시 분석)**:

    ```bison
    %{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h" // AST 노드 구조체와 생성 함수들을 포함

    int yylex(void);         // Flex에서 생성된 렉서 함수
    void yyerror(const char *s); // 파싱 오류 처리 함수
    %}

    // Flex와 Bison 간에 전달되는 값(Semantic Value)의 타입을 정의하는 공용체
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

    // 터미널 심볼(토큰) 선언. <타입>은 %union에서 정의된 멤버 이름.
    %token INT RETURN IF ELSE WHILE FOR
    %token <int_value> NUMBER // NUMBER 토큰은 int_value를 전달
    %token <ident> IDENT     // IDENT 토큰은 ident (문자열)를 전달
    %token EQ NE LT GT LE GE

    // 비터미널 심볼 선언. <타입>은 %union에서 정의된 멤버 이름.
    %type <expr> expr primary
    %type <expr_list> arg_list arg_list_opt
    %type <stmt> stmt vardecl if_stmt while_stmt for_stmt for_init_opt
    %type <stmt_list> stmt_list stmt_list_opt compound_stmt
    %type <param_list> param_list param_list_opt
    %type <function> function
    %type <function_list> func_list program

    // 연산자 우선순위 및 결합성 정의 (가장 낮은 우선순위부터)
    %right '='
    %left EQ NE
    %left LT GT LE GE
    %left '+' '-'
    %left '*' '/'

    %% // 문법 규칙 시작

    // 프로그램 전체 구조
    program
        : func_list                { g_program = $$; } // 전체 프로그램의 AST 노드 (FunctionList)를 전역 변수에 저장
        ;

    // 함수 리스트
    func_list
        : func_list function       { $$ = function_list_append($1, $2); } // 기존 함수 리스트에 새 함수 추가
        | function                 { $$ = function_list_append(NULL, $1); } // 첫 번째 함수
        ;

    // 함수 정의
    function
        : INT IDENT '(' param_list_opt ')' compound_stmt
                                  { $$ = new_function($2, $4, $6); } // 함수 AST 노드 생성
        ;

    // 매개변수 리스트 (파라미터 리스트)
    param_list_opt
        : /* empty */              { $$ = NULL; }
        | param_list               { $$ = $1; }
        ;

    param_list
        : INT IDENT                    { $$ = param_list_append(NULL, $2); }
        | param_list ',' INT IDENT     { $$ = param_list_append($1, $4); }
        ;

    // 복합 문장 (블록)
    compound_stmt
        : '{' stmt_list_opt '}'    { $$ = new_compound_stmt($2); } // 복합 문장 AST 노드 생성
        ;

    stmt_list_opt
        : /* empty */              { $$ = NULL; }
        | stmt_list                { $$ = $1; }
        ;

    stmt_list
        : stmt_list stmt           { $$ = stmt_list_append($1, $2); }
        | stmt                     { $$ = stmt_list_append(NULL, $1); }
        ;

    // 문장 (Statement)
    stmt
        : vardecl ';'              { $$ = $1; }
        | RETURN expr ';'          { $$ = new_return_stmt($2); }
        | expr ';'                 { $$ = new_expr_stmt($1); }
        | if_stmt                  { $$ = $1; }
        | while_stmt               { $$ = $1; }
        | for_stmt                 { $$ = $1; }
        ;

    // 조건문 (If Statement)
    if_stmt
        : IF '(' expr ')' compound_stmt                 { $$ = new_if_stmt($3, $5, NULL); } // else 없는 if
        | IF '(' expr ')' compound_stmt ELSE compound_stmt { $$ = new_if_stmt($3, $5, $7); } // else 있는 if
        ;

    // 반복문 (While Statement)
    while_stmt
        : WHILE '(' expr ')' compound_stmt              { $$ = new_while_stmt($3, $5); }
        ;

    // 반복문 (For Statement)
    for_stmt
        : FOR '(' for_init_opt ';' for_cond_opt ';' for_increment_opt ')' compound_stmt
                                  { $$ = new_for_stmt($3, $5, $7, $9); }
        ;

    for_init_opt // for 초기화 부분
        : /* empty */              { $$ = NULL; }
        | INT IDENT                { $$ = new_vardecl_stmt($2, NULL); }
        | INT IDENT '=' expr       { $$ = new_vardecl_stmt($2, $4); }
        | expr                     { $$ = new_expr_stmt($1); }

    for_cond_opt // for 조건 부분
        : /* empty */              { $$ = NULL; }
        | expr                     { $$ = $1; }

    for_increment_opt // for 증감 부분
        : /* empty */              { $$ = NULL; }
        | expr                     { $$ = $1; }

    // 변수 선언
    vardecl
        : INT IDENT                { $$ = new_vardecl_stmt($2, NULL); }
        | INT IDENT '=' expr       { $$ = new_vardecl_stmt($2, $4); }
        ;

    // 표현식 (Expression)
    expr
        : expr '+' expr            { $$ = new_binop_expr(BIN_ADD, $1, $3); } // 이항 연산자 표현식
        | expr '-' expr            { $$ = new_binop_expr(BIN_SUB, $1, $3); }
        | expr '*' expr            { $$ = new_binop_expr(BIN_MUL, $1, $3); }
        | expr '/' expr            { $$ = new_binop_expr(BIN_DIV, $1, $3); }
        | expr EQ expr             { $$ = new_binop_expr(BIN_EQ, $1, $3); }
        | expr NE expr             { $$ = new_binop_expr(BIN_NE, $1, $3); }
        | expr LT expr             { $$ = new_binop_expr(BIN_LT, $1, $3); }
        | expr GT expr             { $$ = new_binop_expr(BIN_GT, $1, $3); }
        | expr LE expr             { $$ = new_binop_expr(BIN_LE, $1, $3); }
        | expr GE expr             { $$ = new_binop_expr(BIN_GE, $1, $3); }
        | IDENT '=' expr           { $$ = new_assign_expr($1, $3); } // 할당 표현식
        | primary                  { $$ = $1; }
        ;

    // Primary 표현식 (숫자, 식별자, 함수 호출, 괄호)
    primary
        : NUMBER                   { $$ = new_int_expr($1); }
        | IDENT                    { $$ = new_var_expr($1); }
        | IDENT '(' arg_list_opt ')' { $$ = new_call_expr($1, $3); } // 함수 호출
        | '(' expr ')'             { $$ = $2; }
        ;

    // 인자 리스트
    arg_list_opt
        : /* empty */              { $$ = NULL; }
        | arg_list                 { $$ = $1; }
        ;

    arg_list
        : expr                     { $$ = expr_list_append(NULL, $1); }
        | arg_list ',' expr        { $$ = expr_list_append($1, $3); }
        ;

    %% // 사용자 코드 시작

    void yyerror(const char *s) {
        fprintf(stderr, "parse error: %s\n", s);
        // exit(1); // 오류 발생 시 종료 (필요에 따라 활성화)
    }
    ```

*   **주요 요소 설명**:
    *   `%{ ... %}` 블록: Flex와 마찬가지로, 이 블록 안의 내용은 생성된 `parser.tab.c` 파일의 최상단에 그대로 복사됩니다. `stdio.h`, `stdlib.h`, `ast.h` 등의 헤더 파일을 포함하고, `yylex()` 및 `yyerror()` 함수의 선언이 포함됩니다.
    *   `%union`: Flex에서 `yylval`을 통해 전달된 '의미 값(semantic value)'의 타입을 정의하는 공용체입니다. 파서의 각 심볼(터미널 및 비터미널)은 이 `union`의 특정 멤버를 사용하여 값을 저장하거나 전달합니다. 예를 들어 `NUMBER` 토큰은 `int_value`를, `IDENT` 토큰은 `ident`를 사용합니다. `expr`, `stmt` 등은 AST 노드의 포인터를 저장합니다.
    *   `%token`: 터미널 심볼(Lexer에서 반환되는 토큰)을 선언합니다. `<타입>`은 해당 토큰이 전달할 값의 `yylval` 멤버 이름을 지정합니다.
    *   `%type`: 비터미널 심볼(문법 규칙의 왼쪽 부분)을 선언합니다. 마찬가지로 `<타입>`은 이 비터미널이 파싱 결과로 전달할 값의 `yylval` 멤버 이름을 지정합니다.
    *   `%start program`: 파싱의 시작 심볼을 `program`으로 지정합니다.
    *   **연산자 우선순위 및 결합성**: `%left`, `%right` 지시어를 사용하여 연산자의 우선순위와 결합성(좌측 또는 우측)을 정의합니다. 나열된 순서대로 우선순위가 낮아지며, 같은 줄에 있는 연산자는 동일한 우선순위를 가집니다. `EXPR: EXPR '+' EXPR` 와 같이 애매모호한 문법이 있을 때 파싱 충돌을 해결하는 데 사용됩니다.
    *   `%%` 블록 (문법 규칙):
        *   `비터미널 : 규칙 { 액션 }` 형태로 문맥 자유 문법(Context-Free Grammar) 규칙을 정의합니다.
        *   **`$$`와 `$n`**: 각 규칙의 액션 블록 내에서 `$$`는 현재 비터미널(규칙의 왼쪽 심볼)의 의미 값을 나타내고, `$1`, `$2`, ... `$n`은 규칙의 오른쪽 심볼들의 의미 값을 나타냅니다. 이 프로젝트에서는 `new_binop_expr`, `new_if_stmt`, `new_function` 등과 같은 함수들을 호출하여 AST 노드를 생성하고, 그 포인터를 `$$`에 할당하여 상위 규칙으로 전달하는 방식으로 AST를 구축합니다.
        *   **예시: 이항 연산자 표현식**:
            ```bison
            expr : expr '+' expr { $$ = new_binop_expr(BIN_ADD, $1, $3); }
            ```
            이 규칙은 `expr + expr` 형태의 구문을 파싱합니다. `$1`은 첫 번째 `expr`의 의미 값(AST 노드), `$3`은 세 번째 `expr`의 의미 값을 나타냅니다. `new_binop_expr` 함수는 두 피연산자 AST 노드와 연산자 타입(`BIN_ADD`)을 받아 새로운 이항 연산자 AST 노드를 생성하고, 이 노드의 포인터가 `$$`에 저장되어 상위 규칙으로 전달됩니다.
        *   **예시: `if` 문**:
            ```bison
            if_stmt : IF '(' expr ')' compound_stmt { $$ = new_if_stmt($3, $5, NULL); }
            ```
            `$3`은 조건식(`expr`)의 AST 노드, `$5`는 `then` 블록(`compound_stmt`)의 AST 노드입니다. `new_if_stmt`는 이들을 인자로 받아 `if` 문 AST 노드를 생성합니다.
    *   `yyerror(const char *s)`: 파서가 문법 오류를 발견했을 때 호출되는 함수입니다. 일반적으로 오류 메시지를 출력하고, 경우에 따라 프로그램 실행을 종료할 수 있습니다.
*   **시험 대비**: Bison 문법 (`%{ %}`, `%union`, `%token`, `%type`, `%%`), 문법 규칙 정의 방법, `$$` 및 `$n`을 이용한 AST 노드 생성 및 값 전달, 연산자 우선순위 및 결합성 정의, 파싱 충돌 (Shift-Reduce, Reduce-Reduce)의 개념 및 해결 전략, `yyerror` 함수 역할.

다음은 **4. 추상 구문 트리 (Abstract Syntax Tree - AST)** 섹션을 채울 차례입니다.
`Assignment_My_Compiler/include/ast.h` 및 `Assignment_My_Compiler/src/ast.c` 파일을 분석하여 AST 노드 구조, 타입, 생성 함수 등을 추가하겠습니다.


## 4. 추상 구문 트리 (Abstract Syntax Tree - AST)

*   **개념**: 파스 트리에서 불필요한 구문 정보를 제거하고, 프로그램의 의미를 추상적으로 표현한 트리 구조입니다. 컴파일러의 후반 단계(의미 분석, 중간 코드 생성, 코드 생성)에서 주로 사용됩니다.
*   **주요 파일**: `ast.h` (AST 노드 구조체 정의), `ast.c` (AST 노드 생성 및 조작 함수 구현)
    *   예시 경로: `Assignment_My_Compiler/include/ast.h`, `Assignment_My_Compiler/src/ast.c`
*   **AST 노드 구조 (`ast.h` 예시 분석)**:

    `ast.h` 파일은 다양한 AST 노드(표현식, 문장, 함수 정의 등)의 타입과 구조를 정의합니다. `union`을 사용하여 노드 타입에 따라 다른 데이터를 효율적으로 저장합니다.

    ```c
    #ifndef AST_H
    #define AST_H

    // 전방 선언 (Forward declarations)
    typedef struct Expr Expr;
    typedef struct ExprList ExprList;
    typedef struct Stmt Stmt;
    typedef struct StmtList StmtList;
    typedef struct Param Param;
    typedef struct ParamList ParamList;
    typedef struct Function Function;
    typedef struct FunctionList FunctionList;

    // 표현식의 종류 (Enum for Expression Kinds)
    typedef enum {
        EXPR_INT,       // 정수 리터럴
        EXPR_VAR,       // 변수
        EXPR_BINOP,     // 이항 연산
        EXPR_CALL,      // 함수 호출
        EXPR_ASSIGN     // 할당 표현식 (예: a = 10)
    } ExprKind;

    // 이항 연산자의 종류 (Enum for Binary Operator Kinds)
    typedef enum {
        BIN_ADD, BIN_SUB, BIN_MUL, BIN_DIV, // 사칙 연산
        BIN_EQ,  BIN_NE,  BIN_LT,  BIN_GT,  BIN_LE, BIN_GE // 비교 연산
    } BinOpKind;

    // 표현식 AST 노드 구조체 (Expression AST Node Structure)
    struct Expr {
        ExprKind kind; // 어떤 종류의 표현식인지 나타내는 필드
        union { // ExprKind에 따라 다른 데이터를 저장하는 공용체
            int int_value; // EXPR_INT일 경우 정수 값
            char *var_name; // EXPR_VAR 또는 EXPR_ASSIGN일 경우 변수 이름
            struct { // EXPR_BINOP일 경우
                BinOpKind op; // 연산자 종류
                Expr *lhs;    // 좌측 피연산자
                Expr *rhs;    // 우측 피연산자
            } binop;
            struct { // EXPR_CALL일 경우
                char *func_name; // 호출할 함수 이름
                ExprList *args;  // 인자 리스트
            } call;
            struct { // EXPR_ASSIGN일 경우 (예: x = y + 1)
                char *var_name; // 할당 대상 변수 이름
                Expr *value;    // 할당될 값 표현식
            } assign_expr;
        } u;
    };

    // 표현식 리스트 (함수 호출 인자 등에 사용)
    struct ExprList {
        Expr *expr;
        ExprList *next;
    };

    // 문장의 종류 (Enum for Statement Kinds)
    typedef enum {
        STMT_EXPR,      // 표현식 문장 (예: x + 1;)
        STMT_RETURN,    // return 문
        STMT_VARDECL,   // 변수 선언 (예: int x = 10;)
        STMT_ASSIGN,    // 할당 문장 (예: x = 10;) - 이 프로젝트에서는 ExprKind의 EXPR_ASSIGN으로 대체 가능성 있음.
        STMT_IF,        // if 문
        STMT_WHILE,     // while 문
        STMT_FOR        // for 문
    } StmtKind;

    // 문장 AST 노드 구조체 (Statement AST Node Structure)
    struct Stmt {
        StmtKind kind; // 문장의 종류
        union { // StmtKind에 따라 다른 데이터를 저장하는 공용체
            Expr *expr; // STMT_EXPR, STMT_RETURN일 경우 포함하는 표현식
            struct { // STMT_VARDECL일 경우
                char *var_name;
                Expr *initial_value; // 초기화 값이 없으면 NULL
            } vardecl;
            struct { // STMT_ASSIGN일 경우
                char *var_name;
                Expr *value;
            } assign;
            struct { // STMT_IF일 경우
                Expr *cond;      // 조건 표현식
                StmtList *then_body; // then 블록 문장 리스트
                StmtList *else_body; // else 블록 문장 리스트 (없으면 NULL)
            } if_stmt;
            struct { // STMT_WHILE일 경우
                Expr *cond;      // 조건 표현식
                StmtList *body;  // 루프 본문 문장 리스트
            } while_stmt;
            struct { // STMT_FOR일 경우
                Stmt *init;      // 초기화 문장 (Stmt_VARDECL 또는 STMT_EXPR)
                Expr *cond;      // 조건 표현식
                Expr *increment; // 증감 표현식
                StmtList *body;  // 루프 본문 문장 리스트
            } for_stmt;
        } u;
        Stmt *next; // 다음 문장으로의 포인터 (StmtList 구현을 위해 사용)
    };

    // 문장 리스트
    struct StmtList {
        Stmt *head;
        Stmt *tail;
    };

    // 함수 매개변수
    struct Param {
        char *name;
        Param *next;
    };

    // 함수 매개변수 리스트
    struct ParamList {
        Param *head;
        Param *tail;
    };

    // 함수 정의 AST 노드
    struct Function {
        char *name;
        ParamList *params;
        StmtList *body;
        Function *next; // 다음 함수 정의로의 포인터
    };

    // 전체 프로그램의 함수 리스트
    struct FunctionList {
        Function *head;
        Function *tail;
    };

    // AST 노드 생성 함수들의 프로토타입
    Expr *new_int_expr(int value);
    Expr *new_var_expr(const char *name);
    Expr *new_binop_expr(BinOpKind op, Expr *lhs, Expr *rhs);
    Expr *new_call_expr(const char *func_name, ExprList *args);
    Expr *new_assign_expr(const char *name, Expr *value);
    ExprList *expr_list_append(ExprList *list, Expr *expr);

    Stmt *new_expr_stmt(Expr *e);
    Stmt *new_return_stmt(Expr *e);
    Stmt *new_vardecl_stmt(const char *name, Expr *initial_value);
    Stmt *new_assign_stmt(const char *name, Expr *value);
    Stmt *new_if_stmt(Expr *cond, StmtList *then_body, StmtList *else_body);
    Stmt *new_while_stmt(Expr *cond, StmtList *body);
    Stmt *new_for_stmt(Stmt *init, Expr *cond, Expr *increment, StmtList *body);
    StmtList *stmt_list_append(StmtList *list, Stmt *stmt);

    ParamList *param_list_append(ParamList *list, const char *name);

    Function *new_function(const char *name, ParamList *params, StmtList *body);
    FunctionList *function_list_append(FunctionList *list, Function *func);

    // 전역 프로그램 AST의 루트 노드
    extern FunctionList *g_program;

    #endif
    ```

*   **AST 노드 생성 (`ast.c` 예시 분석)**:

    `ast.c` 파일은 `ast.h`에 정의된 구조체들을 동적으로 할당하고 초기화하는 함수들을 구현합니다. 파서(Bison)의 액션에서 이 함수들을 호출하여 AST를 구축합니다.

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ast.h"

    FunctionList *g_program = NULL; // 전역 프로그램 AST의 루트 노드 초기화

    // 문자열 복사 헬퍼 함수 (메모리 할당 및 복사)
    static char *strdup_s(const char *s) {
        if (!s) return NULL;
        size_t len = strlen(s) + 1;
        char *p = (char *)malloc(len);
        if (!p) {
            fprintf(stderr, "out of memory\n");
            exit(1);
        }
        memcpy(p, s, len);
        return p;
    }

    // 예시: 정수 리터럴 표현식 노드 생성
    Expr *new_int_expr(int value) {
        Expr *e = (Expr *)calloc(1, sizeof(Expr)); // 메모리 할당 및 0으로 초기화
        if (!e) { /* error handling */ }
        e->kind = EXPR_INT;       // 노드 종류 설정
        e->u.int_value = value;   // 공용체 멤버에 값 저장
        return e;
    }

    // 예시: 이항 연산 표현식 노드 생성
    Expr *new_binop_expr(BinOpKind op, Expr *lhs, Expr *rhs) {
        Expr *e = (Expr *)calloc(1, sizeof(Expr));
        if (!e) { /* error handling */ }
        e->kind = EXPR_BINOP;
        e->u.binop.op = op;
        e->u.binop.lhs = lhs; // 좌측 자식 노드 연결
        e->u.binop.rhs = rhs; // 우측 자식 노드 연결
        return e;
    }

    // 예시: if 문장 노드 생성
    Stmt *new_if_stmt(Expr *cond, StmtList *then_body, StmtList *else_body) {
        Stmt *s = (Stmt *)calloc(1, sizeof(Stmt));
        if (!s) { /* error handling */ }
        s->kind = STMT_IF;
        s->u.if_stmt.cond = cond;
        s->u.if_stmt.then_body = then_body;
        s->u.if_stmt.else_body = else_body; // else 블록이 없으면 NULL
        return s;
    }

    // 예시: 문장 리스트에 문장 추가
    StmtList *stmt_list_append(StmtList *list, Stmt *stmt) {
        if (!stmt) return list;
        if (!list) { // 리스트가 비어있으면 새로 생성
            list = (StmtList *)calloc(1, sizeof(StmtList));
            list->head = list->tail = NULL;
        }
        if (!list->head) { // 리스트가 비어있으면 첫 번째 요소로 설정
            list->head = list->tail = stmt;
        } else { // 리스트의 끝에 추가
            list->tail->next = stmt;
            list->tail = stmt;
        }
        return list;
    }

    // 다른 모든 `new_` 함수들도 유사한 방식으로 노드를 생성하고 초기화합니다.
    // 각 리스트 `_append` 함수는 연결 리스트 형태로 노드를 추가합니다.
    ```

*   **주요 요소 설명**:
    *   **전방 선언 (`typedef struct ...;`)**: 상호 참조(예: `Expr` 구조체가 `ExprList`를 참조하고 `ExprList`가 `Expr`를 참조)를 해결하기 위해 사용됩니다.
    *   **노드 종류 (`ExprKind`, `BinOpKind`, `StmtKind`)**: `enum`을 사용하여 AST 노드의 구체적인 타입을 명확히 구분합니다. 이를 통해 어떤 종류의 표현식/문장인지 쉽게 파악할 수 있습니다.
    *   **공용체 (`union`)**: C 언어의 `union`을 활용하여 하나의 `struct` 내에서 여러 종류의 데이터를 유연하게 저장합니다. `kind` 필드를 통해 현재 `union`의 어떤 멤버가 유효한지 판단합니다. 이는 메모리 사용을 최적화하는 일반적인 방법입니다.
    *   **리스트 구조 (`ExprList`, `StmtList`, `ParamList`, `FunctionList`)**: 여러 표현식, 문장, 매개변수, 함수 등을 순서대로 저장하기 위한 연결 리스트 구조입니다. 각 리스트는 `head`와 `tail` 포인터를 가져 효율적인 추가를 가능하게 합니다.
    *   **AST 노드 생성 함수 (`new_...`)**: `ast.c`에 구현된 이 함수들은 AST 노드에 필요한 메모리를 `calloc`(메모리 할당 및 0 초기화)으로 할당하고, `kind` 필드와 `union`의 적절한 멤버를 초기화한 후, 자식 노드들을 연결하여 완전한 AST 노드를 반환합니다.
        *   `calloc` 사용은 `malloc`보다 안전할 수 있습니다.
        *   `strdup_s`와 같이 문자열을 복사하는 함수는 문자열 리터럴이나 `yytext` 버퍼가 변경될 수 있으므로, AST 노드에 저장하기 전에 항상 별도의 메모리에 복사해야 합니다.
    *   **전역 루트 노드 (`g_program`)**: `parser.y`에서 `program` 규칙의 액션에 의해 파싱된 전체 프로그램의 AST(여기서는 `FunctionList` 형태)가 `g_program` 전역 변수에 저장되어 컴파일러의 다음 단계에서 이 트리를 순회하며 작업을 수행할 수 있도록 합니다.
*   **시험 대비**: AST의 필요성, 파스 트리와의 차이점, `enum`과 `union`을 활용한 유연한 AST 노드 설계 방법, `calloc` 및 `strdup`를 이용한 노드 생성 및 메모리 관리, 연결 리스트를 이용한 노드 리스트 구현, AST 순회 방법(깊이 우선, 너비 우선), AST를 이용한 정보 추출.

다음은 **5. 의미 분석 (Semantic Analysis)** 섹션을 채울 차례입니다.
`9wk/minic_symbol` 및 `9wk/minic_type` 폴더의 파일들을 참고하여 심볼 테이블 구조와 타입 시스템 구현의 예시를 추가하겠습니다. `Assignment_My_Compiler`에는 `sema` 파일이 직접적으로 보이지 않지만, 이들 예제를 통해 일반적인 구현 방식을 설명할 것입니다.


## 5. 의미 분석 (Semantic Analysis)

*   **개념**: 구문 분석이 통과된 프로그램이 언어의 의미 규칙에 맞는지를 검사합니다. 주요 작업으로는 타입 검사(Type Checking), 심볼 테이블 관리(Symbol Table Management), 선언 분석 등이 있습니다. 이 단계에서는 AST를 순회하며 프로그램의 의미적 정확성을 확인하고, 컴파일러의 다음 단계(코드 생성)에 필요한 정보를 수집합니다.
*   **주요 파일**:
    *   `symbol_table.h`, `symbol_table.c` (`9wk/minic_symbol`): 심볼 테이블 구현.
    *   `types.h` (`9wk/minic_type`): 타입 정의.
    *   `sema.h`, `sema.c` (`9wk/minic_type`): 의미 분석의 핵심 로직 (AST 순회, 타입 검사, 심볼 처리).
*   **심볼 테이블 (`symbol_table.h`, `symbol_table.c` 예시 분석)**:

    심볼 테이블은 변수, 함수, 매개변수 등의 식별자에 대한 정보를 저장하고 관리하는 자료구조입니다. 이 프로젝트에서는 해시 테이블과 연결 리스트를 사용하여 구현되었으며, 스코프(scope)를 지원합니다.

    ```c
    // symbol_table.h
    typedef enum { SYM_VAR, SYM_PARAM, SYM_FUNC } SymKind; // 심볼의 종류

    typedef struct Sym {
      const char *name;     // 심볼 이름
      SymKind     kind;     // 심볼 종류 (변수, 파라미터, 함수)
      int         arity;    // 함수의 경우 파라미터 수, 변수는 0
      int         level;    // 스코프 레벨 (전역:0, 함수:1, 블록:2 등)
      TypeKind    tkind;    // (sema.c에서 추가적으로 사용) 심볼의 타입
      struct Sym *next;     // 해시 체인의 다음 심볼
    } Sym;

    // 함수 프로토타입
    void  symtab_init(void);    // 심볼 테이블 초기화
    void  symtab_fini(void);    // 심볼 테이블 해제
    void  scope_push(void);     // 새 스코프 시작
    void  scope_pop(void);      // 현재 스코프 종료
    bool  sym_put(const char *name, SymKind kind, TypeKind tkind, int arity); // 심볼 등록
    Sym*  sym_get(const char *name);    // 이름으로 심볼 찾기
    ```

    ```c
    // symbol_table.c (주요 함수 발췌)
    #define NHASH 211       // 해시 버킷 수

    static Sym* buckets[NHASH]; // 해시 테이블의 버킷 배열
    static int cur_level = 0;   // 현재 스코프 레벨

    // 간단한 해시 함수
    static unsigned h(const char *s){ /* ... */ }

    // 스코프 경계 표시용 가드 노드 생성
    static Sym* make_guard(void){
      Sym* g = (Sym*)calloc(1, sizeof(Sym));
      g->name = NULL; g->level = cur_level; // name이 NULL인 노드로 스코프 경계 표시
      return g;
    }

    // 새 스코프에 진입 (스코프 스택 push)
    void scope_push(void){
      cur_level++;
      for(int i=0;i<NHASH;i++){ // 모든 버킷 앞에 가드 노드 삽입
        Sym* g=make_guard(); g->next=buckets[i]; buckets[i]=g;
      }
    }

    // 현재 스코프에서 선언된 심볼 제거 (스코프 스택 pop)
    void scope_pop(void){
      for(int i=0;i<NHASH;i++){
        Sym* p=buckets[i];
        while(p && p->name!=NULL){ // 가드 노드 전까지 심볼 해제
          Sym* n=p->next; free(p); p=n;
        }
        if(p){ Sym* n=p->next; free(p); buckets[i]=n; } // 가드 노드 제거
      }
      cur_level--;
    }

    // 심볼 등록
    bool sym_put(const char *name, SymKind kind, TypeKind tkind, int arity){
      unsigned idx=h(name);
      // 현재 스코프(가드 노드 전까지)에서 중복 선언 검사
      for(Sym* p=buckets[idx]; p && p->name!=NULL; p=p->next){
        if(strcmp(p->name,name)==0) return false; // 중복이면 실패
      }
      // 새 심볼 생성 및 해시 테이블에 연결
      Sym* s=(Sym*)calloc(1,sizeof(Sym));
      s->name=name; s->kind=kind; s->tkind=tkind; s->arity=arity; s->level=cur_level;
      s->next=buckets[idx]; buckets[idx]=s;
      return true;
    }

    // 이름으로 심볼 검색 (가장 가까운 스코프부터)
    Sym* sym_get(const char *name){
      unsigned idx=h(name);
      for(Sym* p=buckets[idx]; p; p=p->next){
        if(p->name && strcmp(p->name,name)==0) return p; // 이름이 일치하는 심볼 반환
      }
      return NULL; // 찾지 못함
    }
    ```

    *   **심볼(`Sym`) 구조**: `name`, `kind` (변수/파라미터/함수), `arity` (함수의 인자 수), `level` (스코프 깊이), `tkind` (심볼의 타입) 등의 정보를 저장합니다.
    *   **해시 테이블 기반 구현**: `buckets` 배열과 `h` 해시 함수를 사용하여 심볼을 효율적으로 저장하고 검색합니다. 충돌 처리(collision resolution)는 연결 리스트(체인 방식)를 사용합니다.
    *   **스코프 관리**:
        *   `cur_level` 변수가 현재 스코프의 깊이를 추적합니다.
        *   `scope_push()` 함수는 새로운 스코프에 진입할 때 호출됩니다. 이 때 각 해시 버킷의 연결 리스트 맨 앞에 `name`이 `NULL`인 특별한 노드(guard node)를 삽입하여 현재 스코프의 경계를 표시합니다. `cur_level`을 증가시킵니다.
        *   `scope_pop()` 함수는 현재 스코프를 나갈 때 호출됩니다. `guard node`를 만나기 전까지의 모든 심볼 노드를 해제하여 현재 스코프에서 선언된 심볼들을 제거합니다. `cur_level`을 감소시킵니다.
        *   `sym_put()`은 현재 스코프 내에서 이름 중복을 검사하고, `sym_get()`은 가장 가까운(현재 스코프의) 심볼부터 찾아 상위 스코프로 올라가며 검색합니다.

*   **타입 정의 (`types.h` 예시 분석)**:

    의미 분석 단계에서 사용될 기본적인 타입들을 정의합니다.

    ```c
    // types.h
    typedef enum {
      TY_INT, TY_FLOAT, TY_CHAR, TY_VOID, // 기본 타입
      TY_ERROR // 오류 전파용
    } TypeKind;
    ```

*   **의미 분석 로직 (`sema.c` 예시 분석)**:

    `sema.c` 파일은 AST를 순회하며 실제 의미 분석을 수행하는 핵심 모듈입니다. 심볼 테이블을 활용하여 선언/사용 검사, 타입 검사 등을 진행합니다.

    ```c
    // sema.c (주요 함수 발췌)
    #include "sema.h"
    #include "symbol_table.h" // 심볼 테이블 사용
    #include "types.h"        // 타입 정의 사용
    #include "ast.h"          // AST 노드 정의 사용 (sema.h에서 Node*로 일반화되어 있음)
    #include <stdio.h>
    #include <string.h>

    int sema_errors = 0; // 의미 분석 중 발생한 오류 수

    // 오류 메시지 출력 헬퍼 함수
    static void err(int line, const char* fmt, const char* a){ /* ... */ }

    // 문자열 타입 이름을 내부 TypeKind로 매핑
    static TypeKind type_from_str(const char* s){ /* ... */ }

    // 이항 연산자의 결과 타입 추론 (간단한 타입 승격 규칙)
    static TypeKind binop_type(TypeKind a, TypeKind b){
      if(a==TY_ERROR || b==TY_ERROR) return TY_ERROR;
      if(a==TY_CHAR) a=TY_INT;
      if(b==TY_CHAR) b=TY_INT;
      if(a==TY_FLOAT || b==TY_FLOAT) return TY_FLOAT; // float가 섞이면 float
      return TY_INT; // 아니면 int
    }

    // 전방 선언 (순환 참조 문제 해결)
    static TypeKind check_expr(Node* n); // 표현식의 타입 확인 및 추론
    static void     visit_stmt(Node* s, TypeKind func_ret); // 문장 방문
    static void     visit_block(Node* comp, TypeKind func_ret); // 블록 방문

    // 변수 선언 처리
    static void handle_decl(Node* decl){
      TypeKind t = type_from_str(decl->child[0]->op); // 선언된 타입 (예: "int")
      Node* list = decl->child[1]; // 선언자 리스트 (변수 이름, 초기화 표현식)
      for(int i=0;i<list->nchild;i++){
        Node* idecl = list->child[i];
        const char* name = idecl->op; // 변수 이름
        if(!sym_put(name, SYM_VAR, t, 0)) // 심볼 테이블에 변수 등록 (중복 선언 검사)
          err(idecl->line, "redeclaration of '%s'", name);
        if(idecl->nchild==1 && idecl->child[0]){ // 초기화 표현식이 있다면
          TypeKind rt = check_expr(idecl->child[0]); // 초기화 표현식의 타입 확인
          if(t==TY_INT && rt==TY_FLOAT)
            err(idecl->line, "narrowing init from float to int in '%s'", name); // 묵시적 형변환 경고/에러
          // ... void 타입 사용 오류 검사 등
        }
      }
    }

    // 함수 정의 처리
    static void handle_func_def(Node* f){
      TypeKind ret = type_from_str(f->child[0]->op); // 반환 타입
      const char* fname = f->op; // 함수 이름
      int arity = f->child[1]->nchild; // 파라미터 수

      if(!sym_put(fname, SYM_FUNC, ret, arity)) // 심볼 테이블에 함수 등록 (중복 정의 검사)
        err(f->line, "redefinition of function '%s'", fname);

      scope_push(); // 함수 스코프 시작

      // 파라미터 등록
      for(int i=0;i<arity;i++){
        Node* p = f->child[1]->child[i];
        TypeKind pt = type_from_str(p->child[0]->op); // 파라미터 타입
        if(!sym_put(p->op, SYM_PARAM, pt, 0))
          err(p->line, "duplicate parameter '%s'", p->op); // 중복 파라미터 검사
      }

      visit_block(f->child[2], ret); // 함수 본문(블록) 방문하여 의미 분석 진행

      scope_pop(); // 함수 스코프 종료
    }

    // 표현식 타입 확인 및 추론
    static TypeKind check_expr(Node* n){
      if(!n) return TY_VOID;
      switch(n->kind){
        case NK_INT:   return TY_INT; // 정수 리터럴 -> int 타입
        case NK_VAR: { // 변수 사용
          Sym* s = sym_get(n->op); // 심볼 테이블에서 변수 검색
          if(!s){ err(n->line, "use of undeclared identifier '%s'", n->op); return TY_ERROR; } // 미선언 변수 사용 오류
          return s->tkind; // 변수의 타입 반환
        }
        case NK_ASSIGN: { // 할당 표현식
          Sym* s = sym_get(n->op);
          if(!s){ err(n->line, "assignment to undeclared identifier '%s'", n->op); return TY_ERROR; }
          TypeKind rt = check_expr(n->child[0]); // 할당될 값의 타입 확인
          if(s->tkind==TY_INT && rt==TY_FLOAT)
            err(n->line, "narrowing assignment to '%s' (float→int)", n->op); // 묵시적 형변환 오류
          return s->tkind; // 할당식의 결과 타입은 좌변의 타입
        }
        case NK_BINOP: { // 이항 연산
          TypeKind a = check_expr(n->child[0]); // 좌변 타입
          TypeKind b = check_expr(n->child[1]); // 우변 타입
          return binop_type(a,b); // 이항 연산 결과 타입 추론
        }
        case NK_CALL: { // 함수 호출
          Sym* f = sym_get(n->op); // 심볼 테이블에서 함수 검색
          if(!f || f->kind!=SYM_FUNC){
            err(n->line, "call to undeclared function '%s'", n->op); return TY_ERROR;
          }
          int nargs = n->child[0] ? n->child[0]->nchild : 0; // 전달된 인자 수
          if(f->arity != nargs) // 인자 수 불일치 검사
            err(n->line, "wrong # of args in call to '%s'", n->op);
          // 인자 타입 검사 (여기서는 void 타입 사용 금지만)
          // 실제로는 파라미터 타입과 인자 타입의 일치 여부도 검사해야 함
          return f->tkind; // 함수의 반환 타입
        }
        // ... 다른 표현식 종류에 대한 타입 확인
      }
      return TY_ERROR;
    }

    // AST 루트에서 의미 분석 시작
    void sema_run(Node *root){
      symtab_init();    // 심볼 테이블 초기화
      scope_push();     // 전역 스코프 시작
      // root (NK_TRANSLATION_UNIT)를 방문하여 외부 선언 및 함수 정의 처리
      // ...
      scope_pop();      // 전역 스코프 종료
    }
    ```

*   **주요 요소 설명**:
    *   **타입(`TypeKind`)**: `types.h`에 정의된 `TY_INT`, `TY_FLOAT` 등의 열거형을 사용하여 컴파일러 내부에서 타입을 표현합니다. `TY_ERROR`는 오류 발생 시 타입을 전파하는 데 사용됩니다.
    *   **타입 추론 및 검사**:
        *   `type_from_str()`: 소스 코드의 문자열 타입(예: "int")을 내부 `TypeKind`로 변환합니다.
        *   `binop_type()`: 이항 연산자의 피연산자 타입들을 기반으로 결과 타입을 추론합니다 (예: `int + float`의 결과는 `float`).
        *   `check_expr()`: AST의 표현식 노드를 순회하며 각 표현식의 타입을 결정하고, 타입 규칙에 위배되는 경우 오류를 보고합니다. (예: 미선언 변수 사용, float에서 int로의 묵시적 형변환).
    *   **심볼 관리 및 스코프**:
        *   `sema_run()` 함수는 `symtab_init()`으로 심볼 테이블을 초기화하고, `scope_push()`로 전역 스코프를 시작합니다.
        *   `handle_decl()` 함수는 변수 선언 시 `sym_put()`을 사용하여 심볼 테이블에 변수 이름과 타입, 종류를 등록하고, 중복 선언을 검사합니다. 초기화 표현식의 타입도 확인합니다.
        *   `handle_func_def()` 함수는 함수 정의 시 함수 이름, 반환 타입, 인자 수를 심볼 테이블에 등록하고, 새로운 스코프를 열어 파라미터들을 등록합니다. 함수 본문을 방문하기 전에 `scope_push()`를, 본문 분석 후 `scope_pop()`을 호출하여 스코프를 적절히 관리합니다.
    *   **오류 보고**: `err()` 헬퍼 함수를 사용하여 의미 분석 중에 발견된 오류를 표준 오류 스트림에 출력하고 `sema_errors` 카운터를 증가시킵니다.
    *   **AST 순회**: `visit_tu()`, `handle_decl()`, `handle_func_def()`, `visit_block()`, `visit_stmt()`, `check_expr()`와 같은 함수들을 통해 AST를 깊이 우선(Depth-First) 방식으로 순회하며 각 노드에 해당하는 의미 분석 작업을 수행합니다.

*   **시험 대비**:
    *   심볼 테이블의 역할, 구현 방식 (해시 테이블, 스코프 관리), `scope_push/pop` 및 `sym_put/get` 함수의 동작 원리.
    *   타입 시스템의 설계 (`TypeKind`), 타입 검사 규칙 (이항 연산, 할당, 함수 호출 등), 타입 승격 및 묵시적 형변환 처리.
    *   미선언 식별자, 중복 선언/정의, 인자 수 불일치 등의 의미 오류 감지 방법.
    *   AST 순회를 통한 의미 분석 과정 이해.

다음은 **6. 중간 코드 생성 (Intermediate Code Generation - IR)** 섹션을 채울 차례입니다.
`10wk/minic_ir` 폴더의 파일들을 참고하여 IR 구조와 생성 함수의 예시를 추가하겠습니다.


## 6. 중간 코드 생성 (Intermediate Code Generation - IR)

*   **개념**: AST를 기계 독립적인 형태의 중간 표현(Intermediate Representation, IR)으로 변환하는 단계입니다. IR은 소스 코드와 타겟 기계 코드 사이의 추상화 계층 역할을 하며, 최적화 및 다양한 타겟 아키텍처로의 코드 생성을 용이하게 합니다. 이 프로젝트에서는 주로 3-주소 코드(Three-Address Code, TAC) 형태의 IR을 사용한 것으로 보입니다.
*   **주요 파일**: `ir.h` (IR 구조체 정의), `ir.c` (IR 관리 및 출력), `codegen.c` (AST에서 IR 생성)
    *   예시 경로: `10wk/minic_ir/include/ir.h`, `10wk/minic_ir/src/ir.c`, `10wk/minic_ir/src/codegen.c`
*   **IR 구조 (`ir.h` 예시 분석)**:

    IR 명령어는 연산(opcode)과 최대 3개의 피연산자(operand)를 가지는 3-주소 코드 형태로 표현됩니다.

    ```c
    // ir.h
    typedef enum {
        IR_ADD,     // dst = src1 + src2
        IR_SUB,     // dst = src1 - src2
        IR_MUL,     // dst = src1 * src2
        IR_DIV,     // dst = src1 / src2
        IR_LOADI,   // dst = src1 (상수 로드)
        IR_MOV,     // dst = src1 (값 이동)
        IR_PRINT    // print src1 (결과 출력)
        // ... 조건문, 점프 등 다양한 IR 연산자가 추가될 수 있음
    } IROp; // IR 연산 코드

    typedef struct IR {
        IROp op;            // 어떤 연산인지
        char dst[32];       // 목적지 (Destination, 결과가 저장될 임시 변수 또는 변수 이름)
        char src1[32];      // 첫 번째 소스 피연산자
        char src2[32];      // 두 번째 소스 피연산자 (이항 연산에 사용, 필요 없으면 빈 문자열 "")
        struct IR* next;    // 단일 연결 리스트로 IR들을 연결하기 위한 포인터
    } IR;

    // 함수 프로토타입
    void emit(IROp op, const char* dst, const char* s1, const char* s2); // 새 IR 노드를 만들어 리스트에 추가
    void print_ir(void);    // IR 리스트 전체 출력 (디버깅용)
    char* new_temp(void);   // 새 임시 변수 이름 생성 (예: t0, t1, ...)
    void free_ir(void);     // 리스트 전체 free 및 상태 초기화
    ```

*   **IR 관리 및 출력 (`ir.c` 예시 분석)**:

    `ir.c`는 IR 명령어 리스트를 관리하고 출력하는 함수들을 포함합니다.

    ```c
    // ir.c (주요 함수 발췌)
    static IR* head = NULL; // IR 리스트의 헤드
    static IR* tail = NULL; // IR 리스트의 테일
    static int temp_id = 0; // 임시 변수 번호

    // 새로운 임시 변수 이름 생성 (예: t0, t1, t2...)
    char* new_temp(void) {
        char* buf = (char*)malloc(32); // 메모리 할당
        sprintf(buf, "t%d", temp_id++); // "t" + 번호 형식으로 이름 생성
        return buf;
    }

    // 새로운 IR 노드를 생성하여 리스트에 추가
    void emit(IROp op, const char* dst, const char* s1, const char* s2)
    {
        IR* n = (IR*)calloc(1, sizeof(IR)); // 새 IR 노드 할당
        n->op = op;
        // 각 필드에 값 복사 (strncpy는 버퍼 오버플로우 방지)
        if (dst) strncpy(n->dst, dst, sizeof(n->dst) - 1);
        if (s1) strncpy(n->src1, s1, sizeof(n->src1) - 1);
        if (s2) strncpy(n->src2, s2, sizeof(n->src2) - 1);

        // IR 리스트의 끝에 추가
        if (!head) head = n;
        else       tail->next = n;
        tail = n;
    }

    // 현재 생성된 모든 IR 명령어들을 출력
    void print_ir(void)
    {
        for (IR* p = head; p; p = p->next) {
            switch (p->op) {
                // 각 IR 연산자에 따라 포맷팅하여 출력
                case IR_LOADI: printf("%s = %s\n", p->dst, p->src1); break;
                case IR_MOV:   printf("%s = %s\n", p->dst, p->src1); break;
                case IR_ADD:   printf("%s = %s + %s\n", p->dst, p->src1, p->src2); break;
                // ... 다른 연산자들 출력
                case IR_PRINT: printf("print %s\n", p->src1); break;
            }
        }
    }
    ```

*   **AST에서 IR 생성 (`codegen.c` 예시 분석)**:

    `codegen.c`는 AST를 순회하며 해당 노드에 맞는 IR 명령어들을 생성하고 `emit` 함수를 통해 IR 리스트에 추가하는 역할을 합니다. 여기서는 단순한 표현식에 대한 IR 생성 예시만 보입니다.

    ```c
    // codegen.c (주요 함수 발췌)
    #include "ast.h" // AST 노드 정의
    #include "ir.h"  // IR 구조체 및 emit, new_temp 함수 사용

    // 표현식 AST 노드로부터 IR을 생성하고, 결과가 저장된 임시 변수 이름을 반환
    char* gen(AST* node) // 여기서는 AST* 대신 Expr*을 받는 것이 더 적합할 수 있음. (minic_ir의 AST가 더 단순)
    {
        if (!node) return NULL; // 노드가 없으면 NULL 반환 (오류 처리)

        switch (node->type) { // AST 노드 타입에 따라 다른 IR 생성
            case AST_INT: { // 정수 리터럴
                char* t = new_temp(); // 결과를 저장할 새 임시 변수 생성
                char buf[32];
                sprintf(buf, "%d", node->value); // 정수 값을 문자열로 변환
                emit(IR_LOADI, t, buf, ""); // t = 값 형태의 IR 명령어 생성
                return t; // 임시 변수 이름 반환
            }
            case AST_VAR: // 변수 참조
                return node->name ? strdup(node->name) : NULL; // 변수 이름 자체를 피연산자로 사용

            case AST_ADD: // 덧셈 연산
            case AST_SUB: // 뺄셈 연산
            case AST_MUL: // 곱셈 연산
            case AST_DIV: { // 나눗셈 연산
                char* left = gen(node->left);   // 좌측 피연산자 AST에서 IR 재귀적으로 생성
                char* right = gen(node->right); // 우측 피연산자 AST에서 IR 재귀적으로 생성
                char* t = new_temp();           // 연산 결과를 저장할 새 임시 변수 생성

                // AST 노드 타입에 맞는 IR 연산 코드(IROp)를 사용하여 IR 명령어 생성
                switch (node->type) {
                    case AST_ADD: emit(IR_ADD, t, left, right); break;
                    case AST_SUB: emit(IR_SUB, t, left, right); break;
                    case AST_MUL: emit(IR_MUL, t, left, right); break;
                    case AST_DIV: emit(IR_DIV, t, left, right); break;
                    default: break;
                }
                return t; // 결과 임시 변수 이름 반환
            }
            // ... 다른 AST 노드 타입 (할당, 함수 호출, 조건문 등)에 대한 IR 생성 로직 추가
            default:
                fprintf(stderr, "Unknown AST node type: %d\n", node->type);
                return NULL;
        }
    }
    ```

*   **주요 요소 설명**:
    *   **3-주소 코드 (Three-Address Code, TAC)**: `dst = src1 op src2` 형태의 명령어. 각 연산은 최대 3개의 주소를 가집니다. `IR` 구조체가 이를 명확히 반영합니다.
    *   **`IROp`**: 각 IR 명령어의 종류를 정의하는 열거형입니다.
    *   **임시 변수 (`new_temp()`)**: 중간 계산 결과를 저장하기 위한 가상의 변수입니다. 코드 생성 단계에서 실제 레지스터나 메모리 위치로 매핑됩니다. `t0`, `t1`, `t2`와 같은 고유한 이름으로 생성됩니다.
    *   **`emit()` 함수**: 새로운 IR 명령어를 생성하고, 이를 전역 IR 리스트(`head`, `tail`)에 추가하는 역할을 합니다.
    *   **재귀적 IR 생성 (`gen()` 함수)**: `gen` 함수는 AST를 깊이 우선(Depth-First) 방식으로 순회하며 IR을 생성합니다.
        *   리터럴(예: `AST_INT`)이나 변수 참조(`AST_VAR`)는 해당 값을 로드하거나 직접 참조하는 IR을 생성합니다.
        *   이항 연산(예: `AST_ADD`)의 경우, 먼저 좌우측 피연산자에 대해 재귀적으로 `gen`을 호출하여 해당 피연산자의 IR을 생성하고, 그 결과로 얻은 임시 변수들을 사용하여 현재 연산에 대한 IR 명령어를 `emit`합니다.
        *   각 `gen` 호출은 해당 표현식의 최종 결과가 저장된 임시 변수의 이름을 반환합니다.

*   **시험 대비**:
    *   IR의 필요성 및 장점 (기계 독립성, 최적화 용이성).
    *   3-주소 코드의 개념 및 형식.
    *   `IROp`, `IR` 구조체와 같은 IR 명령어의 표현 방법.
    *   `new_temp()`와 같은 임시 변수 관리 전략.
    *   AST를 순회하며 `emit()` 함수를 호출하여 IR을 생성하는 과정. 특히 이항 연산자와 같은 복합 표현식에 대한 IR 생성 방식.

다음은 **7. 코드 생성 (Code Generation - x86 Assembly)** 섹션을 채울 차례입니다.
`Assignment_My_Compiler/src/codegen_x86.c` 및 `11wk/minic_x86` 폴더의 파일들을 참고하여 x86 어셈블리 코드 생성의 예시를 추가하겠습니다.


## 7. 코드 생성 (Code Generation - x86 Assembly)

*   **개념**: 중간 코드(IR) 또는 AST를 타겟 아키텍처(이 프로젝트에서는 x86)의 어셈블리 명령어로 변환하는 단계입니다. 이 단계에서는 실제 CPU가 실행할 수 있는 명령어를 생성하며, 레지스터 할당, 스택 프레임 관리, 함수 호출 규약 등을 고려해야 합니다.
*   **타겟**: 32-bit x86 어셈블리 (AT&T 문법 사용)
*   **주요 파일**: `codegen_x86.h`, `codegen_x86.c`
    *   예시 경로: `Assignment_My_Compiler/include/codegen_x86.h`, `Assignment_My_Compiler/src/codegen_x86.c`
*   **전체 코드 생성 흐름 (`codegen_x86.h`, `codegen_x86.c` 예시 분석)**:

    `codegen_x86.c`는 `gen_x86_program` 함수를 통해 AST의 `FunctionList`를 순회하며 각 함수에 대한 어셈블리 코드를 생성합니다. 각 함수는 `gen_function`에서 처리되고, 함수 내의 문장들은 `gen_stmt`, 표현식은 `gen_expr`을 통해 재귀적으로 어셈블리 코드로 변환됩니다.

    ```c
    // codegen_x86.h
    #include "ast.h"
    void gen_x86_program(FunctionList *prog); // 프로그램의 AST를 받아 x86 어셈블리 코드를 생성하는 진입점
    ```

    ```c
    // codegen_x86.c (주요 함수 및 로직 발췌)
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ast.h"
    #include "codegen_x86.h"

    // 지역 변수 및 매개변수 정보를 저장하는 구조체
    typedef struct {
        const char *name;
        int offset;       /* ebp 기준 음수 오프셋 (지역 변수), 양수 오프셋 (매개 변수) */
    } Var;

    // 현재 스코프의 변수/매개변수를 저장하는 배열 (실제로는 스택 기반 관리가 더 일반적)
    // 여기서는 함수별로 재할당하여 관리
    static Var vars[128]; // 최대 128개의 변수/매개변수

    // 변수의 옵셋을 찾는 헬퍼 함수
    static int find_var(const Var *vars, int n, const char *name) { /* ... */ }

    // 지역 변수 및 매개 변수의 스택 프레임 내 오프셋 할당
    static void alloc_locals_and_params(Function *f, Var *vars, int *var_count, int *stack_size) {
        int count = 0;
        int local_offset = -4;  // 첫 지역 변수는 ebp-4
        int param_offset = 8;   // 첫 매개 변수는 ebp+8 (ebp, return address 다음에)

        // 매개변수 할당 (ebp+8, ebp+12, ...)
        if (f->params) {
            Param *p = f->params->head;
            while (p) {
                vars[count].name = p->name;
                vars[count].offset = param_offset;
                count++;
                param_offset += 4;
                p = p->next;
            }
        }

        // 지역 변수 할당 (ebp-4, ebp-8, ...)
        if (f->body) {
            Stmt *s = f->body->head;
            while (s) {
                if (s->kind == STMT_VARDECL) { // 변수 선언 문장
                    if (find_var(vars, count, s->u.vardecl.var_name) < 0) { // 이미 할당되지 않은 경우
                        vars[count].name = s->u.vardecl.var_name;
                        vars[count].offset = local_offset;
                        count++;
                        local_offset -= 4;
                    }
                }
                // for 문의 초기화 부분에 변수 선언이 있을 경우 처리
                else if (s->kind == STMT_FOR && s->u.for_stmt.init && s->u.for_stmt.init->kind == STMT_VARDECL) {
                    if (find_var(vars, count, s->u.for_stmt.init->u.vardecl.var_name) < 0) {
                        vars[count].name = s->u.for_stmt.init->u.vardecl.var_name;
                        vars[count].offset = local_offset;
                        count++;
                        local_offset -= 4;
                    }
                }
                s = s->next;
            }
        }
        *var_count = count;
        // 스택에 할당할 전체 크기 계산 (16바이트 정렬 등을 고려할 수 있음)
        *stack_size = (-local_offset) - 4; 
    }

    // AST 표현식을 x86 어셈블리로 변환 (결과는 eax에 저장)
    static void gen_expr(Expr *e, Var *vars, int var_count) {
        if (!e) return;

        switch (e->kind) {
        case EXPR_INT: // 정수 리터럴
            printf("    movl $%d, %%eax\n", e->u.int_value); // eax에 상수 값 로드
            break;
        case EXPR_VAR: // 변수 참조
            load_var_to_eax(e->u.var_name, vars, var_count); // 변수 값을 스택에서 eax로 로드
            break;
        case EXPR_BINOP: // 이항 연산
            gen_expr(e->u.binop.rhs, vars, var_count);  // 우측 피연산자 평가 (결과 eax)
            printf("    pushl %%eax\n");                 // eax 값을 스택에 임시 저장
            gen_expr(e->u.binop.lhs, vars, var_count);  // 좌측 피연산자 평가 (결과 eax)
            printf("    popl %%ecx\n");                   // 스택에 저장했던 우측 피연산자를 ecx로 가져옴 (eax=lhs, ecx=rhs)

            switch (e->u.binop.op) {
            case BIN_ADD: printf("    addl %%ecx, %%eax\n"); break; // eax += ecx
            case BIN_SUB: printf("    subl %%ecx, %%eax\n"); break; // eax -= ecx
            case BIN_MUL: printf("    imull %%ecx, %%eax\n"); break; // eax *= ecx
            case BIN_DIV:
                printf("    cdq\n");                      // eax를 edx:eax로 부호 확장 (idivl 준비)
                printf("    idivl %%ecx\n");               // eax /= ecx (몫은 eax, 나머지는 edx)
                break;
            // 비교 연산 (결과를 0 또는 1로 eax에 저장)
            case BIN_EQ: case BIN_NE: case BIN_LT: case BIN_GT: case BIN_LE: case BIN_GE:
                printf("    cmpl %%ecx, %%eax\n");         // eax와 ecx 비교 (eax - ecx)
                printf("    movl $0, %%eax\n");             // eax를 0으로 초기화
                if (e->u.binop.op == BIN_EQ) printf("    sete %%al\n");   // ZF=1 이면 al=1 (eax=ecx)
                else if (e->u.binop.op == BIN_NE) printf("    setne %%al\n"); // ZF=0 이면 al=1 (eax!=ecx)
                else if (e->u.binop.op == BIN_LT) printf("    setl %%al\n");   // SF!=OF 이면 al=1 (eax<ecx)
                else if (e->u.binop.op == BIN_GT) printf("    setg %%al\n");   // SF=OF & ZF=0 이면 al=1 (eax>ecx)
                else if (e->u.binop.op == BIN_LE) printf("    setle %%al\n");  // SF!=OF | ZF=1 이면 al=1 (eax<=ecx)
                else if (e->u.binop.op == BIN_GE) printf("    setge %%al\n");  // SF=OF 이면 al=1 (eax>=ecx)
                break;
            default: break;
            }
            break;
        case EXPR_CALL: // 함수 호출
            // 인자들을 역순으로 스택에 push (cdecl 호출 규약)
            void push_args_reverse(ExprList* args) {
                if (!args) return;
                push_args_reverse(args->next); // 재귀적으로 호출하여 역순으로 처리
                gen_expr(args->expr, vars, var_count); // 인자 표현식 평가 (결과 eax)
                printf("    pushl %%eax\n");
            }
            push_args_reverse(e->u.call.args);
            int argc = 0; // 인자 수 계산
            ExprList *cur = e->u.call.args;
            while(cur) { argc++; cur = cur->next; }

            printf("    call _%s\n", e->u.call.func_name); // 함수 호출
            if (argc > 0) { // 호출자가 스택 정리
                printf("    addl $%d, %%esp\n", argc * 4);
            }
            // 함수 반환 값은 eax에 저장되어 있음
            break;
        case EXPR_ASSIGN: { // 할당 표현식 (예: a = b + c)
            gen_expr(e->u.assign_expr.value, vars, var_count); // 할당될 값 평가 (결과 eax)
            int idx = find_var(vars, var_count, e->u.assign_expr.var_name);
            int off = vars[idx].offset;
            printf("    movl %%eax, %d(%%ebp)\n", off); // eax 값을 변수 위치에 저장
            break;
        }
        default: break;
        }
    }

    // AST 문장을 x86 어셈블리로 변환
    static void gen_stmt(Stmt *s, Var *vars, int var_count, const char *func_name) {
        if (!s) return;

        switch (s->kind) {
        case STMT_VARDECL: // 변수 선언 (초기화 있을 수 있음)
            if (s->u.vardecl.initial_value) {
                gen_expr(s->u.vardecl.initial_value, vars, var_count); // 초기 값 평가 (결과 eax)
                int idx = find_var(vars, var_count, s->u.vardecl.var_name);
                int off = vars[idx].offset;
                printf("    movl %%eax, %d(%%ebp)\n", off); // eax 값을 변수 위치에 저장
            }
            break;
        case STMT_ASSIGN: // 할당 문장 (예: x = 10;)
            gen_expr(s->u.assign.value, vars, var_count); // 할당 값 평가
            int idx = find_var(vars, var_count, s->u.assign.var_name);
            int off = vars[idx].offset;
            printf("    movl %%eax, %d(%%ebp)\n", off); // eax 값을 변수 위치에 저장
            break;
        case STMT_EXPR: // 표현식 문장 (예: foo(); 또는 x + y;)
            gen_expr(s->u.expr, vars, var_count); // 표현식 평가 (결과는 사용되지 않고 버려짐)
            break;
        case STMT_RETURN: // return 문
            gen_expr(s->u.expr, vars, var_count); // 반환 값 평가 (결과 eax)
            printf("    jmp .Lend_%s\n", func_name); // 함수 종료 레이블로 점프
            break;
        case STMT_IF: { // if 문
            static int if_count = 0;
            int current_if_id = if_count++;
            char else_label[64], end_if_label[64];
            snprintf(else_label, sizeof(else_label), ".L_else_%d", current_if_id);
            snprintf(end_if_label, sizeof(end_if_label), ".L_endif_%d", current_if_id);

            gen_expr(s->u.if_stmt.cond, vars, var_count); // 조건 평가 (결과 eax)
            printf("    cmpl $0, %%eax\n");                 // eax가 0이면 (거짓)
            if (s->u.if_stmt.else_body) {
                printf("    je %s\n", else_label);         // else 블록으로 점프
            } else {
                printf("    je %s\n", end_if_label);       // if 블록 끝으로 점프
            }

            // then_body (참일 때 실행)
            Stmt *current_then_stmt = s->u.if_stmt.then_body->head;
            while (current_then_stmt) { gen_stmt(current_then_stmt, vars, var_count, func_name); current_then_stmt = current_then_stmt->next; }
            printf("    jmp %s\n", end_if_label); // then_body 실행 후 if 블록 끝으로 점프

            // else_body (거짓일 때 실행, 있을 경우)
            if (s->u.if_stmt.else_body) {
                printf("%s:\n", else_label); // else 레이블 정의
                Stmt *current_else_stmt = s->u.if_stmt.else_body->head;
                while (current_else_stmt) { gen_stmt(current_else_stmt, vars, var_count, func_name); current_else_stmt = current_else_stmt->next; }
            }
            printf("%s:\n", end_if_label); // if 블록 끝 레이블 정의
            break;
        }
        case STMT_WHILE: { // while 문
            static int while_count = 0;
            int current_while_id = while_count++;
            char loop_label[64], end_loop_label[64];
            snprintf(loop_label, sizeof(loop_label), ".L_loop_%d", current_while_id);
            snprintf(end_loop_label, sizeof(end_loop_label), ".L_endloop_%d", current_while_id);

            printf("%s:\n", loop_label); // 루프 시작 레이블
            gen_expr(s->u.while_stmt.cond, vars, var_count); // 조건 평가
            printf("    cmpl $0, %%eax\n");
            printf("    je %s\n", end_loop_label); // 거짓이면 루프 종료

            // 루프 본문
            Stmt *current_body_stmt = s->u.while_stmt.body->head;
            while (current_body_stmt) { gen_stmt(current_body_stmt, vars, var_count, func_name); current_body_stmt = current_body_stmt->next; }
            printf("    jmp %s\n", loop_label); // 본문 실행 후 루프 시작으로 점프

            printf("%s:\n", end_loop_label); // 루프 종료 레이블
            break;
        }
        case STMT_FOR: { // for 문
            static int for_count = 0;
            int current_for_id = for_count++;
            char loop_label[64], end_loop_label[64], increment_label[64];
            snprintf(loop_label, sizeof(loop_label), ".L_for_loop_%d", current_for_id);
            snprintf(end_loop_label, sizeof(end_loop_label), ".L_for_endloop_%d", current_for_id);
            snprintf(increment_label, sizeof(increment_label), ".L_for_increment_%d", current_for_id);

            // 1. 초기화 (init)
            if (s->u.for_stmt.init) { gen_stmt(s->u.for_stmt.init, vars, var_count, func_name); }

            printf("%s:\n", loop_label); // 조건 검사 레이블

            // 2. 조건 (cond)
            if (s->u.for_stmt.cond) {
                gen_expr(s->u.for_stmt.cond, vars, var_count);
                printf("    cmpl $0, %%eax\n");
                printf("    je %s\n", end_loop_label);
            }

            // 3. 루프 본문
            Stmt *current_body_stmt = s->u.for_stmt.body->head;
            while (current_body_stmt) { gen_stmt(current_body_stmt, vars, var_count, func_name); current_body_stmt = current_body_stmt->next; }

            // 4. 증감 (increment)
            printf("%s:\n", increment_label); // 증감식 레이블
            if (s->u.for_stmt.increment) { gen_expr(s->u.for_stmt.increment, vars, var_count); }

            printf("    jmp %s\n", loop_label); // 조건 검사로 다시 점프

            printf("%s:\n", end_loop_label); // 루프 종료 레이블
            break;
        }
        default: break;
        }
    }

    // 개별 함수에 대한 x86 어셈블리 코드 생성
    static void gen_function(Function *f) {
        // 지역 변수 및 매개 변수 정보 초기화 및 할당
        Var vars_for_func[128];
        int var_count = 0;
        int stack_size = 0;
        alloc_locals_and_params(f, vars_for_func, &var_count, &stack_size);

        // 함수 시작 레이블 및 .globl 지시어
        int is_main = (strcmp(f->name, "main") == 0);
        if (is_main) { printf("    .globl _main\n"); printf("_main:\n"); }
        else { printf("    .globl _%s\n", f->name); printf("_%s:\n", f->name); }

        // 함수 프롤로그: 스택 프레임 설정
        printf("    pushl %%ebp\n");                 // 이전 ebp를 스택에 저장
        printf("    movl %%esp, %%ebp\n");            // 현재 esp를 ebp로 설정 (새로운 스택 프레임 시작)
        if (stack_size > 0) { printf("    subl $%d, %%esp\n", stack_size); } // 지역 변수 공간 확보

        // 함수 본문 내 문장들 코드 생성
        char end_label[64];
        snprintf(end_label, sizeof(end_label), ".Lend_%s", f->name);

        if (f->body) {
            Stmt *s = f->body->head;
            while (s) {
                gen_stmt(s, vars_for_func, var_count, f->name); // 문장 코드 생성
                s = s->next;
            }
        }

        // 함수 에필로그: 스택 프레임 정리 및 반환
        printf("%s:\n", end_label); // 함수 종료 레이블
        if (is_main && !has_return_stmt(f->body)) { // main 함수에 명시적 return 없으면 0 반환
            printf("    movl $0, %%eax\n");
        }
        printf("    leave\n"); // movl %ebp, %esp; popl %ebp 과 동일
        printf("    ret\n\n"); // 함수 호출자로 복귀
    }

    // 전체 프로그램에 대한 x86 어셈블리 코드 생성 (진입점)
    void gen_x86_program(FunctionList *prog) {
        if (!prog) { fprintf(stderr, "No program.\n"); return; }
        printf("    .text\n"); // 코드 섹션 시작

        Function *f = prog->head;
        while (f) { gen_function(f); f = f->next; }
    }
    ```

*   **주요 요소 설명**:
    *   **32-bit x86 어셈블리 (AT&T 문법)**:
        *   레지스터 이름 앞에 `%` (예: `%eax`, `%ebp`).
        *   소스, 목적지 순서 (예: `movl src, dst`).
        *   메모리 참조 `offset(%base_reg, %index_reg, scale)` (예: `8(%ebp)`).
        *   `l` 접미사는 4바이트(long) 연산을 의미.
    *   **레지스터 사용**:
        *   `%eax`: 표현식의 결과 값, 함수 반환 값 저장.
        *   `%ebp`: 스택 프레임 베이스 포인터. 현재 스택 프레임의 기준점.
        *   `%esp`: 스택 포인터. 스택의 최상단을 가리킴.
        *   `%ecx`, `%edx`: 임시 저장 공간으로 활용.
    *   **스택 프레임 관리 (함수 프롤로그/에필로그)**:
        *   **프롤로그**:
            1.  `pushl %ebp`: 이전 스택 프레임의 베이스 포인터 저장.
            2.  `movl %esp, %ebp`: 현재 스택 포인터를 새 베이스 포인터로 설정.
            3.  `subl $stack_size, %esp`: 지역 변수 및 임시 저장을 위한 공간을 스택에 할당.
        *   **에필로그**:
            1.  `leave`: `movl %ebp, %esp` (스택 포인터를 ebp로 되돌려 지역 변수 공간 해제) + `popl %ebp` (이전 스택 프레임의 ebp 복원)과 동일.
            2.  `ret`: 함수 호출자로 복귀.
    *   **지역 변수 및 매개 변수 접근**:
        *   `alloc_locals_and_params` 함수가 AST를 분석하여 각 함수 내의 지역 변수 및 매개 변수들의 `ebp` 기준 오프셋을 계산합니다.
        *   **지역 변수**: 음수 오프셋 (`ebp-4`, `ebp-8`, ...).
        *   **매개 변수**: 양수 오프셋 (`ebp+8`, `ebp+12`, ...).
        *   `movl %d(%%ebp), %%eax`: `ebp` 기준 오프셋의 메모리 값을 `eax` 레지스터로 로드.
        *   `movl %%eax, %d(%%ebp)`: `eax` 레지스터의 값을 `ebp` 기준 오프셋의 메모리에 저장.
    *   **표현식 코드 생성 (`gen_expr`)**:
        *   정수 리터럴: `movl $값, %eax`.
        *   변수 참조: `load_var_to_eax` 호출.
        *   이항 연산: 우측 피연산자를 먼저 계산하여 스택에 `push`하고, 좌측 피연산자를 계산한 후 스택에서 우측 피연산자를 `pop`하여 연산을 수행합니다. 결과는 `eax`에 저장됩니다. (예: `addl %ecx, %eax`).
        *   비교 연산: `cmpl` 명령어로 비교하고, `set` 명령 (예: `sete`, `setne`)으로 `al` 레지스터(eax의 하위 1바이트)에 0 또는 1을 설정하여 조건의 참/거짓을 나타냅니다.
        *   함수 호출 (`gen_call`):
            1.  인자들을 **역순으로** 스택에 `pushl` 합니다. (C 호출 규약 `cdecl`).
            2.  `call _함수이름`: 지정된 함수를 호출합니다.
            3.  `addl $인자_크기, %esp`: 호출자가 스택에 push한 인자들을 정리합니다.
        *   할당 (`EXPR_ASSIGN`): 우측 값을 계산하여 `eax`에 저장한 후, 좌측 변수의 메모리 위치에 `movl %eax, 변수_오프셋(%ebp)`로 저장합니다.
    *   **문장 코드 생성 (`gen_stmt`)**:
        *   `STMT_RETURN`: 반환 값을 `eax`에 넣고 `jmp .Lend_함수이름`으로 함수 에필로그로 바로 이동합니다.
        *   **제어 흐름 (`if`, `while`, `for`)**:
            1.  고유한 레이블을 생성하여 분기 지점을 표시합니다 (예: `.L_else_0`, `.L_endif_0`).
            2.  조건식을 평가한 후 `cmpl $0, %eax`로 참/거짓을 판별하고, `je` (같으면 점프) 또는 `jmp` (무조건 점프) 명령어를 사용하여 적절한 레이블로 분기합니다.

*   **시험 대비**:
    *   x86 어셈블리의 기본 명령어 (`mov`, `add`, `sub`, `imul`, `idiv`, `cmp`, `jmp`, `je`, `call`, `push`, `pop`, `leave`, `ret`).
    *   스택 프레임 구조 (`ebp`, `esp`의 역할, 지역 변수 및 매개 변수의 스택 내 오프셋).
    *   함수 호출 규약 (`cdecl` - 인자 전달 방식, 스택 정리 주체, 반환 값 위치).
    *   레지스터 할당 전략 (이 프로젝트에서는 `eax`를 주요 작업 레지스터로 사용).
    *   AST 노드를 어셈블리 명령어로 변환하는 재귀적 과정.
    *   `if`, `while`, `for` 문과 같은 제어 흐름 구조를 어셈블리 레이블 및 조건부/무조건부 점프로 구현하는 방법.

이제 마지막 섹션인 **8. 예제 워크스루: `Assignment_My_Compiler`** 를 채울 차례입니다.
이 섹션에서는 `Assignment_My_Compiler` 프로젝트의 `main.c` 파일을 분석하여 전체 컴파일러 파이프라인이 어떻게 조립되고 실행되는지 설명하겠습니다.


## 8. 예제 워크스루: `Assignment_My_Compiler`

`Assignment_My_Compiler` 폴더는 위에서 설명한 모든 컴파일러 단계를 통합하여 소스 코드를 x86 어셈블리로 변환하는 최종 프로젝트입니다. `src/main.c` 파일은 이 모든 컴파일러 단계를 조율하는 드라이버 역할을 합니다.

*   **주요 파일**: `src/main.c` (컴파일러 드라이버), `test/` (테스트 케이스)
    *   예시 경로: `Assignment_My_Compiler/src/main.c`

*   **컴파일러 드라이버 (`main.c` 예시 분석)**:

    `main.c`는 프로그램의 진입점으로, 소스 파일을 읽고, 파싱을 시작하며, AST를 기반으로 최종 x86 어셈블리 코드를 생성하는 전체 과정을 관리합니다.

    ```c
    // Assignment_My_Compiler/src/main.c
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"         // AST 구조체 정의 및 전역 AST 루트 g_program
    #include "codegen_x86.h" // x86 코드 생성 함수 gen_x86_program

    // Bison이 생성하는 파서 함수 (extern 선언)
    int yyparse(void);
    // Flex가 사용하는 입력 스트림 (extern 선언)
    extern FILE *yyin;

    int main(int argc, char **argv) {
        /* 1. 입력 파일 처리 */
        // 첫 번째 명령줄 인자가 있으면 해당 파일을 입력으로 사용
        if (argc > 1) {
            yyin = fopen(argv[1], "r"); // 파일 열기
            if (!yyin) {
                perror(argv[1]); // 파일 열기 실패 시 오류 출력
                return 1;
            }
        }
        // 인자가 없으면 기본적으로 stdin (표준 입력)을 사용

        /* 2. 출력 파일 처리 */
        // 표준 출력을 "out.s" 파일로 리다이렉션 (어셈블리 코드 출력을 위해)
        if (!freopen("out.s", "w", stdout)) {
            perror("out.s"); // 파일 리다이렉션 실패 시 오류 출력
            return 1;
        }

        /* 3. 파싱 (어휘 분석 + 구문 분석) */
        // yyparse() 호출. 이 함수는 내부적으로 yylex()를 호출하며 토큰을 읽고,
        // 문법 규칙에 따라 AST를 구축합니다.
        if (yyparse() != 0) { // 파싱 중 오류 발생 시 0이 아닌 값 반환
            fprintf(stderr, "Parsing failed.\n");
            return 1;
        }

        /* 4. AST 확인 및 코드 생성 */
        // 파싱이 성공적으로 완료되면 g_program 전역 변수에 전체 프로그램의 AST가 저장됩니다.
        if (!g_program) {
            fprintf(stderr, "No program parsed. AST is empty.\n");
            return 1;
        }

        // g_program (AST)을 기반으로 x86 어셈블리 코드 생성 시작
        // 생성된 코드는 freopen을 통해 "out.s" 파일에 기록됩니다.
        gen_x86_program(g_program);

        // 성공적으로 컴파일 완료
        return 0;
    }
    ```

*   **컴파일러 전체 흐름**:

    1.  **입력 처리**: `main` 함수는 명령줄 인자를 통해 소스 코드 파일의 경로를 받습니다. `fopen`을 사용하여 파일을 열고, `yyin` 전역 변수에 할당하여 Flex(Lexer)가 이 파일로부터 입력을 읽도록 합니다. (인자가 없으면 표준 입력 사용).
    2.  **출력 리다이렉션**: `freopen("out.s", "w", stdout)` 함수를 사용하여 표준 출력 스트림(`stdout`)을 `out.s` 파일로 변경합니다. 이는 코드 생성기가 `printf` 함수를 호출하여 어셈블리 코드를 `stdout`에 출력할 때, 그 내용이 `out.s` 파일에 저장되도록 합니다.
    3.  **파싱**: `yyparse()` 함수를 호출하여 어휘 분석(Flex)과 구문 분석(Bison)을 시작합니다. `yyparse()`는 소스 파일을 읽어 토큰화하고, 정의된 문법 규칙에 따라 AST를 구축합니다. 성공적으로 파싱되면, `g_program` 전역 변수(AST의 루트 노드)에 완전한 AST가 저장됩니다.
    4.  **코드 생성**: `gen_x86_program(g_program)` 함수를 호출합니다. 이 함수는 구축된 AST(`g_program`)를 순회하며 각 AST 노드에 해당하는 x86 어셈블리 코드를 생성하고, 이 코드를 `stdout` (즉, `out.s` 파일)에 출력합니다.
    5.  **결과**: 최종적으로 `out.s` 파일에는 입력된 소스 코드를 컴파일한 x86 어셈블리 코드가 담기게 됩니다. 이 어셈블리 파일은 외부 어셈블러(예: `nasm`, `gcc -c`)를 통해 오브젝트 파일로, 링커를 통해 실행 가능한 바이너리로 변환될 수 있습니다.

*   **테스트 케이스 (`test/` 디렉토리)**:

    `Assignment_My_Compiler/test/` 디렉토리에는 다양한 `test_*.c` 파일들이 포함되어 있습니다. 이 파일들은 컴파일러가 특정 구문(산술 연산, 변수 할당, `if`문, `while`문, `for`문, 함수 호출 등)을 올바르게 처리하는지 검증하기 위한 소스 코드 예시입니다. 이 테스트 파일들을 컴파일러로 처리하고 `out.s`를 확인하거나, 어셈블 후 실행하여 기대하는 결과가 나오는지 확인함으로써 컴파일러의 기능을 검증할 수 있습니다. 예를 들어, `test_for.c`를 컴파일하여 `for` 문이 어떻게 어셈블리 코드로 변환되는지 학습할 수 있습니다.

**결론**:

이 자료집은 `D:\Git\ComplierInKonkuk` 디렉토리에 있는 컴파일러 코드베이스의 핵심적인 개념과 구현 방식을 상세히 설명했습니다. 각 섹션의 내용과 코드 예시를 통해 컴파일러의 각 단계가 어떻게 작동하는지 이해하고, 기말고사 준비에 큰 도움이 되기를 바랍니다. 궁금한 점이 있거나 특정 부분에 대한 추가 설명이 필요하면 언제든지 질문해주세요.