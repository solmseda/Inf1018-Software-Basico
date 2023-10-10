/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  for (i = 0, p = nums; i != 4; i++, p++)
    if ((*p % 2) == 0)
      printf("%d\n", *p);
  return 0;
}
*/

.data
nums:  .int  10, -21, -30, 45
Sf:  .string "%d\n"    # string de formato para printf

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)
/********************************************************/

    movl  $0, %ebx  /* ebx = 0; */
    movq  $nums, %r12  /* r12 = &nums */

L1:
    cmpl  $4, %ebx  /* if (ebx == 4) ? */
    je  L2          /* goto L2 */

    /* Compara o valor do bit mais significativo em r12 com 1, se for verdadeiro o numero não é par
    então pula para o END que finaliza o programa, caso não seja vedadeiro o numero é par então 
    printa o número e retorna para o loop */

    movl    (%r12), %r13d
    movl    (%r12), %eax
    andl    $1, %r13d
    cmpl    $1, %r13d
    je     END

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
    movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
    movl    %eax, %esi   /* segundo parametro  (inteiro) */
    call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

L3:
    addl  $1, %ebx  /* ebx += 1; */
    addq  $4, %r12  /* r12 += 4; */
    jmp  L1         /* goto L1; */

END:
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
    movq  $0, %rax  /* rax = 0  (valor de retorno) */
    movq  -8(%rbp), %rbx
    movq  -16(%rbp), %r12
    leave
    ret      
/***************************************************************/