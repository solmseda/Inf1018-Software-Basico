/*
float foo (double a, float b) {
  return (a+b)*(a-b);
}
*/

.text
.globl foo
foo:
    pushq       %rbp
    movq        %rsp, %rbp
    subq        $16, %rsp
    movss       %xmm1, -12(%rbp)    # salva b

    cvtsd2ss    %xmm0, %xmm0        # float(a)
    movsd       %xmm0, -8(%rbp)     # salva a convertido para float
    addss       -8(%rbp), %xmm1      # (a + b)
    movss       -12(%rbp), %xmm0     # recupera b
    subss       -8(%rbp), %xmm0      # (a - b)
    mulss       %xmm0, %xmm1        # (a + b) + (a - b)
    movss       %xmm1, %xmm0        # retorna o resultado
    
    leave
    ret
