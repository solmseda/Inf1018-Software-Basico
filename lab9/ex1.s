/*
int add (int a, int b, int c) {
    return a+b+c;
}
*/

.text
.globl add

add:
    pushq   %rbp
    movq    %rsp, %rbp

    addl    %edi, %esi
    addl    %esi, %edx
    movl    %edx, %eax

    leave
    ret
