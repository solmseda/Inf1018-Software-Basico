#include<stdio.h>
#include<math.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff));
#define getsig(x)  ((x)>>31 & 1);
#define getexp(x)  ((x)>>23 & 0xff);
#define getfrac(x) ((x) & 0x7fffff);

typedef union { 
    float f;
    unsigned int i;
} U;

float int2float(int i){
    if (i == 0){
        return 0.0f;
    }

    U fConverted;
    int sign = (i < 0) ? 1 : 0;
    if (sign) {
        i = -i;
    }

    int exp = (int)log2(i);
    int shift = 23 - exp;
    int frac;
    if (shift < 0) {
        shift = 0;
    }

    frac = i << shift;

    exp += 127;

    fConverted.i = makefloat(sign, exp, frac);

    return fConverted.f;

}

int main() {
    int i;

    printf("\n******** int2float ****************\n");
    i = 0;
    printf(" %d -> %+10.4f\n", i, int2float(i));
    i = 1;  
    printf(" %d -> %+10.4f\n", i, int2float(i));
    i = -1;  
    printf(" %d -> %10.4f\n", i, int2float(i));
    i = 0x7fffffff;  
    printf(" %d -> %+10.4f\n", i, int2float(i));
    i = -i;
    printf(" %d -> %+10.4f\n", i, int2float(i));
    i = 12345;
    printf(" %d -> %+10.4f\n", i, int2float(i));
    i = -12345;
    printf(" %d -> %+10.4f\n", i, int2float(i));
    return 0;
}