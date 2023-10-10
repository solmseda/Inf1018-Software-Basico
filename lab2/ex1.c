#include <stdio.h>

void dump (void *p, int n) {
    unsigned char *p1 = p;
    while (n--) {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}

int main (void) {
    int i = 10000;
    long l = 10000;
    short s = 10000;
    char a = 'a';
    char asc = 97;
    char p[] = "7509";

    printf("Dump de inteiro: \n");
    dump(&i, sizeof(i));

    printf("\nDump de long: \n");
    dump(&l, sizeof(l));

    printf("\nDump de short: \n");
    dump(&s, sizeof(s));

    printf("\nDump de char a: \n");
    dump(&a, sizeof(a));

    printf("\nDump de char 97: \n");
    dump(&asc, sizeof(asc));

    printf("\nDump da string 7509: \n");
    dump(&p, sizeof(p));

    return 0;
}