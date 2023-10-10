#include<stdio.h>

int is_little(){
    int i = 1000;
    unsigned char *p = (unsigned char)&i;
    if(p < p+1)
        return 1;
    return 0;
}

int main(void){
    int little = is_little();
    if(little == 1){
        printf("A maquina é little-endian.\n");
    }
    else{
        printf("A maquina é big-endian.\n");
    }
    return 0;
}