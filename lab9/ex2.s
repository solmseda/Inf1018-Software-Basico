/*
int fat (int n) {
    if (n==0) return 1;
    else return n*fat(n-1);
}
*/

.text
.globl fat

fat:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $8, %rsp
    movq    %rbx, -8(%rbp)

    movl    %edi, %eax   /* Move n para %eax */

    cmpl    $0, %eax     /* if (n == 0) return 1; */
    je      if

    movq   %rax, %rbx   /* Salve o valor atual de n em rbx */
    dec     %eax        /* n-- */
    movl    %eax, %edi
    call    fat
    imull   %ebx, %eax

    jmp     end

if:
    movl    $1, %eax      /* Se n for zero, retorne 1 */

end:
    movq    -8(%rbp), %rbx
    leave
    ret
