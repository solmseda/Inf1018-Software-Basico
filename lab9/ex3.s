/*
void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
}
*/

.text
.globl foo

foo:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)

    movq    $0, %ebx        /* i */
    movq    $0, r12         /* s = 0 */

for:
    cmpq    %esi, %ebx      /* if i == n */
    je      end

    incq    ebx             /* i++ */

end:
    movq    -8(%rbp), %rbx
    movq    -8(%rbp), %r12
    leave
    ret