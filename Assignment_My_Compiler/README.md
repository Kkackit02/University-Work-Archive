# Mini C Compiler

This project implements a Mini C compiler that translates a subset of the C language into x86-64 assembly code.

## Features

The compiler supports the following features:
- Variable declaration and assignment (`int x = 10;`)
- Arithmetic operations (`+`, `-`, `*`, `/`)
- Comparison operations (`==`, `!=`, `<`, `>`, `<=`, `>=`)
- Conditional statements (`if`, `if-else`)
- Loop statements (`while`, `for`)
- Function definitions and calls

## Dependencies

To build and run this compiler, you need the following tools:
- `flex` (Lexical Analyzer Generator)
- `bison` (Parser Generator)
- `gcc` (GNU Compiler Collection)
- `make` (Build Automation Tool)

## Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
    cd Assignment_My_Compiler
    ```
2.  **Build the compiler:**
    Run `make all` to build the `minic_x86` executable. This will generate the lexer and parser source files, compile all components, and link them into the final compiler executable.
    ```bash
    make all
    ```

## Usage

To compile a Mini C source file (`.c` extension) into x86-64 assembly code (`out.s`), use the `minic_x86` executable:

```bash
./minic_x86 <source_file.c>
```
This will generate an `out.s` file in the current directory.

To compile the generated assembly code (`out.s`) into an executable program, use `make prog`:

```bash
make prog
```
This will create an executable named `prog`.

To run the compiled program:

```bash
./prog
```
The program's exit code will be the return value of its `main` function.

## Example

Let's say you have a file named `example.c`:

```c
int main() {
    int a = 10;
    int b = 20;
    int sum = a + b;
    if (sum > 20) {
        return sum;
    }
    return 0;
}
```

1.  **Compile the Mini C code:**
    ```bash
    ./minic_x86 example.c
    ```
    This will generate `out.s`.

2.  **Compile the assembly code:**
    ```bash
    make prog
    ```
    This will create `prog`.

3.  **Run the program:**
    ```bash
    ./prog
    ```
    The exit code will be `30` (10 + 20 = 30, which is > 20, so it returns 30).

## Test Cases

The following test cases are provided to demonstrate the compiler's functionality. Each test case is a Mini C source file, and the expected exit code after compilation and execution is noted.

| File Name           | Purpose                                                              | Expected Exit Code |
| :------------------ | :------------------------------------------------------------------- | :----------------- |
| `test.c`            | Function call with arithmetic (`add(10, 20)`)                       | 30                 |
| `test_gt.c`         | Greater than comparison (`10 > 5`)                                   | 1                  |
| `test_lt.c`         | Less than comparison (`10 < 5`)                                      | 0                  |
| `test_if_true.c`    | `if` statement with true condition                                   | 42                 |
| `test_if_false.c`   | `if-else` statement with false condition                             | 99                 |
| `test_assign.c`     | Variable declaration and assignment                                  | 5                  |
| `test_arithmetic.c` | Complex arithmetic expression (`10 + 5 * 2 - 3 / 1`)                 | 17                 |
| `test_nested_if.c`  | Nested `if-else` statements                                          | 2                  |
| `test_while.c`      | `while` loop for summing numbers (1 to 5)                            | 15                 |
| `test_for.c`        | `for` loop for summing numbers (1 to 5)                              | 15                 |

To run a specific test case, for example `test_for.c`:

```bash
./minic_x86 test_for.c
make prog
./prog
echo $? # Check the exit code (on Linux/macOS) or use 'echo %errorlevel%' (on Windows)
```

