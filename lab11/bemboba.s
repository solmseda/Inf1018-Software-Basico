/*
    int bemboba (int num) {
    int local[4];
    int *a;
    int i;

    for (i=0,a=local;i<4;i++) {
        *a = num;
        a++;
    }
    return addl (local, 4);
}
*/

.data
local:  .int   0, 0, 0, 0

.text
.globl bemboba

bemboba:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %r12, -8(%rbp)
    movq    %r13, -16(%rbp)

    movq    $0, %r13        /* i = 0 */
    movq    $local, %r12    /* a = local */

for:
    cmpq    $4, %r13        /* if i=4 */
    jae     end

    /*  
    *a = num;
    a++;
    */
    movl    %edi, (%r12)
    addq    $4, %r12
    incq    %r13
    jmp     for

end:
    movl    $local, %edi
    movq    $4, %rsi
    call    addl

    movq    -8(%rbp), %r12
    movq    -16(%rbp), %r13
    leave
    ret
