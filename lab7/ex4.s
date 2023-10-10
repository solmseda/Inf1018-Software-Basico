/*
int nums[4] = {65, -105, 111, 34};

int main (void) {
  int i;
  int s = 0;

  for (i=0;i<4;i++)
    s = s+nums[i];

  printf ("soma = %d\n", s);

  return 0;
}
*/

.data
nums:  .int  65, -105, 111, 34
Sf:    .string "soma = %d\n"

.text
.globl main

main:
  pushq %rbp
  movq %rsp, %rbp
  subq  $16, %rsp
  movq  %rbx, -8(%rbp)
  movq  %r12, -16(%rbp)

  movl $0, %ebx    /* ebx = 0 (i = 0) */
  movl $0, %eax
  movq $nums, %r12  /* r12 = &nums (endereço do array nums)*/

L1:
  cmpl $4, %ebx    /* if (ebx == 4) */
  je END           /* goto END */

  /* s = s + nums[i]; */
  movl   %ebx, %r11d    /* salva o valor atual do contador em r11d */
  imull  $4, %r11d      /* i * sizeof(T) */

  addq   %r12, %r11    /* soma o valor da posição atual de nums com o valor em r11 */
  addl   (%r11d), %eax
  addl   $1, %ebx        /* ebx += 1; */ 
  jmp L1                  /* Volta ao início do loop */

END:
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call printf           /* Chama a função printf*/

  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret     
