#include<stdio.h>

void dump (void *p, int n) {
    unsigned char *p1 = p;
    while (n--) {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}

unsigned char switch_byte(unsigned char x){
    unsigned char auxLeft = x;
    unsigned char auxRight = x;

    auxLeft = auxLeft << 4;
    auxRight = auxRight >> 4;

    return auxLeft ^ auxRight;
}

unsigned char rotate_left(unsigned char x, int n){
    unsigned char left_bit = x;
    unsigned char removed_bit = x;

    left_bit = left_bit << n;
    removed_bit = removed_bit >> (8-n);

    return removed_bit | left_bit;
}

int main(){
    unsigned char x = 0xAB;
    unsigned char switched, rotated;
    unsigned char y = 0x61;
    
    switched = switch_byte(x);
    printf("Original: %02x\n", x);
    printf("Bit trocado: %02x \n\n", switched);
    
    printf("Original: %02x\n", y);
    rotated = rotate_left(x, 1);
    printf("Bit rotacionado 1 byte: %02x \n", rotated);

    rotated = rotate_left(x, 2);
    printf("Original: %02x\n", y);
    printf("Bit rotacionado 2 bytes: %02x \n", rotated);

    rotated = rotate_left(x, 7);
    printf("Original: %02x\n", y);
    printf("Bit rotacionado 7 bytes: %02x \n", rotated);

    return 0;
}