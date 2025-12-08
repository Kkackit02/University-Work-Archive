# Mini C 컴파일러 프로젝트 설명서

## 1. 언어 개요 및 설계 의도

이 프로젝트에서는 C를 모방한 mini C 컴파일러를 구현하였습니다. 
주요 설계 의도는 어휘 분석, 파싱, 추상 구문 트리(AST) 생성, x86-64 어셈블리 코드 생성 등 
컴파일러 구성의 기본 원리를 구현한 기초적인 컴파일러를 만드는 것입니다.

크게 나만의 언어를 만든다기보단, 최대한 C의 기능을 모방하고자 하였으며, 
수업시간에서 배운 실습 코드를 기반으로 구현하였습니다.


특징:
1) 정적 타입: 타입이 구현되어있지않아 모든 변수는 'int' 타입으로 선언되어야 합니다.
2) 절차 지향: 함수 정의와 호출을 지원합니다.
3) 기본 제어 흐름: 조건문 ('if', 'if-else')과 반복문 ('while', 'for')을 포함합니다.
4) 산술 및 비교 연산: 표준 산술 및 비교 연산을 지원합니다.
5) 구현된 기능은 C언어의 기능을 최대한 구현하고자 하였습니다.

## 2. 문법 정의
Mini C의 문법은 Bison 문법 파일('parser/parser.y')을 사용하여 정의되었습니다. 
아래는 문법을 간략하게 EBNF 형식으로 표현한 것입니다.

'''ebnf
program         ::= func_list

func_list       ::= func_list function
                | function

function        ::= "int" IDENT "(" param_list_opt ")" compound_stmt

param_list_opt  ::= /* empty */
                | param_list

param_list      ::= "int" IDENT
                | param_list "," "int" IDENT

compound_stmt   ::= "{" stmt_list_opt "}"

stmt_list_opt   ::= /* empty */
                | stmt_list

stmt_list       ::= stmt_list stmt
                | stmt

stmt            ::= vardecl ";"
                | RETURN expr ";"
                | expr ";"
                | if_stmt
                | while_stmt
                | for_stmt

if_stmt         ::= IF "(" expr ")" compound_stmt
                | IF "(" expr ")" compound_stmt ELSE compound_stmt

while_stmt      ::= WHILE "(" expr ")" compound_stmt

for_stmt        ::= FOR "(" for_init_opt ";" for_cond_opt ";" for_increment_opt ")" compound_stmt

for_init_opt    ::= /* empty */
                | "int" IDENT
                | "int" IDENT "=" expr
                | expr

for_cond_opt    ::= /* empty */
                | expr

for_increment_opt ::= /* empty */
                | expr

vardecl         ::= "int" IDENT
                | "int" IDENT "=" expr

expr            ::= expr "+" expr
                | expr "-" expr
                | expr "*" expr
                | expr "/" expr
                | expr "==" expr
                | expr "!=" expr
                | expr "<" expr
                | expr ">" expr
                | expr "<=" expr
                | expr ">=" expr
                | IDENT "=" expr  // 할당은 표현식입니다
                | primary

primary         ::= NUMBER
                | IDENT
                | IDENT "(" arg_list_opt ")"
                | "(" expr ")"

arg_list_opt    ::= /* empty */
                | arg_list

arg_list        ::= expr
                | arg_list "," expr
'''



## 3. 전체 구조

1) 어휘 분석 (Lexer): 
'flex' ('parser/lexer.l')를 사용하여 구현했습니다.
Mini C 소스 코드를 읽고 토큰 스트림(예: 키워드, 식별자, 숫자, 연산자)으로 변환해줍니다.

2) 구문 분석 (Parser): 
'bison' ('parser/parser.y')을 사용하여 구현했습니다. 
어휘 분석기(Lexer)에서 받은 토큰 스트림을 사용하여 정의된 문법에 따라 추상 구문 트리(AST)를 구축합니다. 
또한 이 단계에서 구문 오류 보고를 처리합니다.

3) 추상 구문 트리 (AST): 
'include/ast.h'에 정의되고 'src/ast.c'에서 구현되었습니다. 
AST는 프로그램 구조의 중간 표현으로, 구문적 세부 사항을 추상화합니다.

4) 코드 생성: 
'src/codegen_x86.c'에서 구현되었습니다. 
이 과정에서 앞에서 만들어낸 AST를 순회하며 x86-64 어셈블리 코드('out.s')를 생성합니다. 
이 단계에서 지역 변수, 함수 호출(cdecl 호출 규약 사용), 제어 흐름 구조를 관리합니다.

5) 메인 드라이버: 
'src/main.c'에서 입력 파일 읽기부터 어휘 분석기, 파서, 코드 생성기 호출까지 전체 컴파일 과정을 수행합니다.

## 4. 구현된 기능 및 미구현/제한 사항

### 구현된 기능:
- 변수 선언 및 초기화: 초기화를 포함한 'int' 타입 변수를 지원합니다 (예: 'int x;', 'int y = 10;').
- 할당: 할당을 표현식으로 처리합니다 (예: 'x = y + 5;').
- 산술 연산: 덧셈 ('+'), 뺄셈 ('-'), 곱셈 ('*'), 나눗셈 ('/').
- 비교 연산: 같음 ('=='), 다름 ('!='), 미만 ('<'), 초과 ('>'), 이하 ('<='), 이상 ('>=').
- 조건문: 'if' 및 'if-else' 구조.
- 반복문: 'while', 'for' 루프를 지원합니다.
- 함수 정의: 'int'를 반환하고 int 매개변수를 받는 사용자 정의 함수를 지원합니다.
- 함수 호출: 사용자 정의 함수 호출을 지원합니다.
- Return 문: 함수의 return을 구현하였으나, 'int' 정수 값 만을 반환할 수 있습니다.

### 미구현/제한 사항:
- 데이터 타입: 'int' 타입만 지원됩니다. 'char', 'float', 'double'와 같은 다른 타입은 구현하지 못했습니다.
- 배열 및 포인터: 구현되지 않았습니다.
- 전역 변수: 모든 변수는 함수에 지역적입니다.
- 입출력: 콘솔 I/O를 위한 내장 함수(예: 'printf', 'scanf')가 없어 오직 입력 스크립트에서 모든 것을 처리해야합니다.
- 기본적인 논리 관련 기능 미구현 : 'break', 'continue', 'switch' 문을 구현하지 못했습니다.
- 오류 처리: Bison의 기본적인 구문 오류 보고만 가능하고, c에서 제공하는 것처럼 복잡한 오류 처리는 구현되어있지 않습니다.





## 빌드 방법
이 컴파일러를 빌드하고 실행하려면 다음 도구들이 필요합니다:
- 'flex' (어휘 분석기 생성기)
- 'bison' (파서 생성기)
- 'gcc' (GNU 컴파일러 모음)
- 'make' (빌드 자동화 도구)
### 컴파일러 빌드
    'make all'을 실행하여 'minic_x86' 실행 파일을 빌드합니다. 
    이 명령어는 어휘 분석기와 parser 소스 파일을 생성하고, 모든 구성 요소를 컴파일한 후 최종 컴파일러 실행 파일로 링크합니다.
    

## 사용법
Mini C 소스 파일('.c' 확장자)을 x86-64 어셈블리 코드('out.s')로 컴파일하려면 'minic_x86' 실행 파일을 사용합니다:

    ./minic_x86 <source_file.c>
이 명령어는 현재 디렉토리에 'out.s' 파일을 생성합니다.

생성된 어셈블리 코드('out.s')를 실행 가능한 프로그램으로 컴파일하려면 'make prog'를 사용합니다:
    make prog
이 명령어는 'prog'라는 이름의 실행 파일을 생성합니다.

컴파일된 프로그램을 실행하려면:
    ./prog
프로그램의 종료 코드는 'main' 함수의 반환 값이 됩니다.

## 예시
'example.c'라는 이름의 파일이 있다고 가정해 봅시다:

        int main() {
            int a = 10;
            int b = 20;
            int sum = a + b;
            if (sum > 20) {
                return sum;
            }
            return 0;
        }

1.  Mini C 코드 컴파일:

        ./minic_x86 example.c
    'out.s' 파일이 생성됩니다.

3.  어셈블리 코드 컴파일:

        make prog
    'prog' 실행 파일이 생성됩니다.

4.  프로그램 실행:

        /prog
     종료 코드는 '30'이 됩니다 (10 + 20 = 30이고, 20보다 크므로 30을 반환).

## 테스트 케이스

컴파일러의 기능을 보여주기 위해 다음 테스트 케이스들이 제공됩니다. 각 테스트 케이스는 Mini C 소스 파일이며, 컴파일 및 실행 후 예상되는 종료 코드가 명시되어 있습니다.

| 파일명              | 목적                                                                 | 예상 종료 코드 |
| :------------------ | :------------------------------------------------------------------- | :------------- |
| 'test.c'            | 산술 연산을 포함한 함수 호출 ('add(10, 20)')                         | 30             |
| 'test_gt.c'         | 초과 비교 ('10 > 5')                                                 | 1              |
| 'test_lt.c'         | 미만 비교 ('10 < 5')                                                 | 0              |
| 'test_if_true.c'    | 참 조건의 'if'문                                                     | 42             |
| 'test_if_false.c'   | 거짓 조건의 'if-else'문                                              | 99             |
| 'test_assign.c'     | 변수 선언 및 할당                                                    | 5              |
| 'test_arithmetic.c' | 복합 산술 표현식 ('10 + 5 * 2 - 3 / 1')                              | 17             |
| 'test_nested_if.c'  | 중첩 'if-else'문                                                     | 2              |
| 'test_while.c'      | 'while' 루프를 이용한 합계 계산 (1부터 5까지)                        | 15             |
| 'test_for.c'        | 'for' 루프를 이용한 합계 계산 (1부터 5까지)                          | 15             |

특정 테스트 케이스(예: 'test_for.c')를 실행하려면:

    
    ./minic_x86 test_for.c
    make prog
    ./prog
    echo $? # 종료 코드 확인 (Linux/macOS) 또는 'echo %errorlevel%' (Windows) 사용


## 정리

생성된 모든 파일(오브젝트 파일, 실행 파일 등)을 삭제하려면 다음을 실행합니다:
    make clean
