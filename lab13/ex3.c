#include<stdio.h>

typedef int (*funcp) (int x);

int main(){
    unsigned char codigo[] = {0x55, 0x48, 0x89, 0xe5, 0x83, 0xc7, 0x01, 0x89, 0xf8, 0xc9, 0xc3};
    funcp f = (funcp)codigo;
    int i = (*f)(10);

    printf("10+1 = %d\n", i);

    return 0;
}