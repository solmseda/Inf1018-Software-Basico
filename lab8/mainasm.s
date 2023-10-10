/*
#include <stdio.h>
#define LIM 1

int filtro(int x, int lim);

int nums[5] = {3,-5,7,8,-2};

int main() {
  int i;
  int *p = nums;
  for (i = 0; i < 5; i++) {
    printf("%d\n", filtro(*p,LIM));
    p++;
  }
  return 0;
}
*/
.data
nums: .int 3, -5, 7, 8, -2
s1:   .string "%d\n"

.text
.globl main
main:
/* prologo */
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp
    movq  %rbx, -8(%rbp)
    movq  %r12, -16(%rbp)

/* coloque seu codigo aqui */
    movq  $0, %rbx       /* i = 0 */
    movq  $nums, %r12    /* *p = nums */

for:
    cmpq  $5, %rbx       /* if i == 5 */
    jae    end

    movq  (%r12), %rdi
    movl  $1, %esi
    call  filtro
    
    movq  %rax, %rsi
    movq  $s1, %rdi
    call  printf

    incq  %rbx
    addq  $4, %r12
    jmp   for

end:
/* finalizacao */
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret
