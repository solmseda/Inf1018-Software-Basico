/*
int novonum(void) {
  int minhalocal;
  printf("numero: ");
  scanf("%d",&minhalocal);
  return minhalocal;
}
*/

.data
minhalocal:  .int   0
s1: .string "numero:\n"
s2: .string "%d"


.text
.globl novonum

novonum:
  pushq   %rbp
  movq    %rsp, %rbp

  /* printf("numero: "); */
  movq    $s1, %rdi
  call    printf

  /* scanf("%d",&minhalocal); */
  movq    $s2, %rdi
  movq    $minhalocal, %rsi
  call    scanf

  /* Movendo a minhalocal para o registrador de retorno */
  movq    $minhalocal, %rdi
  movl    (%rdi), %eax

  leave
  ret
