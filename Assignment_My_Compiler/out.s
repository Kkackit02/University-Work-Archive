    .text
    .globl _add
_add:
    pushl %ebp
    movl %esp, %ebp
    movl 12(%ebp), %eax
    pushl %eax
    movl 8(%ebp), %eax
    popl %ecx
    addl %ecx, %eax    # lhs + rhs
    jmp .Lend_add
.Lend_add:
    leave
    ret

    .globl _main
_main:
    pushl %ebp
    movl %esp, %ebp
    movl $20, %eax
    pushl %eax
    movl $10, %eax
    pushl %eax
    call _add
    addl $8, %esp
    jmp .Lend_main
.Lend_main:
    leave
    ret

