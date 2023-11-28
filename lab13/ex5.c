#include<stdio.h>

typedef int (*funcp) (int x);

int add (int x) {
  return x+1;
}


int main(){
    unsigned char codigo[] = {0x55, 0x48, 0x89, 0xe5, 0xe8, 0x00, 0x00, 0x00, 0x00, 0xc9, 0xc3};
    funcp f = (funcp)codigo;
    int i;
    long offset = (unsigned char*)&add - codigo - 5;
    
    //converte o endereço para litle endian
    for (int i = 0; i < 4; i++) {
        codigo[5 + i] = (offset >> (i * 8)) & 0xFF;
    }
    
    i = (*f)(10);
    printf("10+1 = %d\n", i);

    return 0;
}