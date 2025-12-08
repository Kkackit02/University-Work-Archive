    .text
    .globl _main
_main:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    # var sum
    movl $0, %eax
    movl %eax, -4(%ebp)   # sum = eax (initialization)
    # var i
    movl $1, %eax
    movl %eax, -8(%ebp)   # i = eax (initialization)
.L_for_loop_0:
    movl $5, %eax
    pushl %eax
    movl -8(%ebp), %eax
    popl %ecx
    cmpl %ecx, %eax
    movl $0, %eax
    setle %al
    cmpl $0, %eax
    je .L_for_endloop_0
    movl -8(%ebp), %eax
    pushl %eax
    movl -4(%ebp), %eax
    popl %ecx
    addl %ecx, %eax    # lhs + rhs
    movl %eax, -4(%ebp)   # sum = eax (assign expr)
.L_for_increment_0:
    movl $1, %eax
    pushl %eax
    movl -8(%ebp), %eax
    popl %ecx
    addl %ecx, %eax    # lhs + rhs
    movl %eax, -8(%ebp)   # i = eax (assign expr)
    jmp .L_for_loop_0
.L_for_endloop_0:
    movl -4(%ebp), %eax
    jmp .Lend_main
.Lend_main:
    leave
    ret

