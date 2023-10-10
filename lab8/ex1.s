/*
  #include <stdlib.h>
  int main() {
    system("ls -ls");
    return 0;
  }
*/

.data
s1: .string "ls -ls"

.text
.globl main
main:
  /* prologo */
    pushq %rbp
    movq  %rsp, %rbp

  /* move s1 para o registrador do 1° argumento */
    movq  $s1, %rdi
    call system

  /* finalizacao */
    leave
    ret
