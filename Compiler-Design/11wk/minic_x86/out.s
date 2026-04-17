    .section .rodata
fmt_print_int:
    .string "%d\n"
fmt_scanf_int:
    .string "%d"
    .text
    .globl main
main:
    pushl %ebp
    movl %esp, %ebp
    movl $40, %eax
    pushl %eax
    movl $2, %eax
    movl %eax, %ebx
    popl %eax
    addl %ebx, %eax
    movl $0, %eax
    leave
    ret
