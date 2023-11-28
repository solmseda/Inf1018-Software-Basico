/*
double foo2 (float a, float b) {
  return sin(a) + cos(b);
}
*/

.text
.globl foo2
foo2:
    pushq       %rbp
    movq        %rsp, %rbp
    subq        $16, %rsp
    movss       %xmm0, -8(%rbp)  # salva o a
    movss       %xmm1, -12(%rbp)  # salva o b

    cvtss2sd    %xmm0, %xmm0    # converte a para double
    call        sin
    movsd       %xmm0, -8(%rbp)  # salva o resultado de sin(a)

    movss       -12(%rbp), %xmm1  # recupera o b
    cvtss2sd    %xmm1, %xmm1    # converte b para double
    movsd       %xmm1, %xmm0    # coloca b em xmm0
    call        cos
    movsd       %xmm0, %xmm1    # salva o resultado de cos(b)

    movsd       -8(%rbp), %xmm0  # recupera o resultado de sin(a)
    cvtsd2ss    %xmm0, %xmm0    # converte o resultado de sin(a) para float
    cvtsd2ss    %xmm1, %xmm1    # converte o resultado de cos(b) para float
    addss       %xmm0, %xmm1    # soma os resultados

    movss       %xmm1, %xmm0    # coloca o resultado em xmm0
    leave
    ret
