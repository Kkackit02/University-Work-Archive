    .text
    .globl _main
_main:
    pushl %ebp
    movl %esp, %ebp
    movl $1, %eax
    pushl %eax
    movl $3, %eax
    popl %ecx
    cdq                  # sign-extend eax -> edx:eax
    idivl %ecx          # lhs / rhs, quotient in eax
    pushl %eax
    movl $2, %eax
    pushl %eax
    movl $5, %eax
    popl %ecx
    imull %ecx, %eax   # lhs * rhs
    pushl %eax
    movl $10, %eax
    popl %ecx
    addl %ecx, %eax    # lhs + rhs
    popl %ecx
    subl %ecx, %eax    # lhs - rhs
    jmp .Lend_main
.Lend_main:
    leave
    ret

