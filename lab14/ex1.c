#include<stdio.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff));
#define getsig(x)  ((x)>>31 & 1);
#define getexp(x)  ((x)>>23 & 0xff);
#define getfrac(x) ((x) & 0x7fffff);

typedef union { 
    float f;
    unsigned int i;
} U;

float float2(float f) {
    U fmult;
    fmult.f = f;
    unsigned int exp = getexp(fmult.i);
    exp += 1;
    unsigned int sig = getsig(fmult.i);
    unsigned int frac = getfrac(fmult.i);
    printf("frac: %d\n", frac);
    fmult.i = makefloat(sig, exp, frac);
    
    return fmult.f;
}

int main(){
    float f;
    printf("\n******** float2 ****************\n");
    f = 0.0;
    printf(" %f -> %f\n", f, float2(f));
    f = 1.0;
    printf(" %f -> %f\n", f, float2(f));
    f = 1.5;
    printf(" %f -> %f\n", f, float2(f));
    f = 2.0;
    printf(" %f -> %f\n", f, float2(f));
    f = 2.5;

    return 0;
}