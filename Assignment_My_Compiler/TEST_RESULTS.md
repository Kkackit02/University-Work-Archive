## test.c
### Source Code
```c
int add(int a, int b) {
    return a + b;
}

int main() {
    return add(10, 20);
}
```
### Execution Result
```bash
Exit Code: 30
```

## test_gt.c
### Source Code
```c
int main() {
    return 10 > 5;
}
```
### Execution Result
```bash
Exit Code: 1
```

## test_lt.c
### Source Code
```c
int main() {
    return 10 < 5;
}
```
### Execution Result
```bash
Exit Code: 0
```

## test_if_true.c
### Source Code
```c
int main() {
    if (1) {
        return 42;
    } else {
        return 99;
    }
}
```
### Execution Result
```bash
Exit Code: 42
```

## test_if_false.c
### Source Code
```c
int main() {
    if (0) {
        return 42;
    } else {
        return 99;
    }
}
```
### Execution Result
```bash
Exit Code: 99
```

## test_assign.c
### Source Code
```c
int main() {
    int x;
    x = 5;
    return x;
}
```
### Execution Result
```bash
Exit Code: 5
```

## test_arithmetic.c
### Source Code
```c
int main() {
    return 10 + 5 * 2 - 3 / 1;
}
```
### Execution Result
```bash
Exit Code: 17
```

## test_nested_if.c
### Source Code
```c
int main() {
    if (1) {
        if (0) {
            return 1;
        } else {
            return 2;
        }
    } else {
        return 3;
    }
}
```
### Execution Result
```bash
Exit Code: 2
```

## test_while.c
### Source Code
```c
int main() {
    int i = 1;
    int sum = 0;
    while (i <= 5) {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}
```
### Execution Result
```bash
Exit Code: 15
```

## test_for.c
### Source Code
```c
int main() {
    int sum = 0;
    for (int i = 1; i <= 5; i = i + 1) {
        sum = sum + i;
    }
    return sum;
}
```
### Execution Result
```bash
Exit Code: 15
```