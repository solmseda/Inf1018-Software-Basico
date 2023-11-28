/*
float foo1 (float a, float b) {
  return sin(a) + b;
}
*/

.text
.globl foo1
foo1:
    pushq       %rbp
    movq        %rsp, %rbp
    subq        $16, %rsp
    movss       %xmm1, -8(%rbp)  # salva o b

    cvtss2sd    %xmm0, %xmm0    # converte a para double
    call        sin
    cvtsd2ss    %xmm0, %xmm0    # converte o resultado de sin(a) para float
    addss       -8(%rbp), %xmm0  # soma b

    leave
    ret
