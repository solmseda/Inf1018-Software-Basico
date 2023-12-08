/*
int foo (int x) {
  return add(x);
}
*/

.text
.globl foo

foo:
    pushq   %rbp
    movq    %rsp, %rbp

    mov    %rdi, %r8

    leave 
    ret
