#include<stdio.h>

float foo (double a, float b);

int main(){
    double a = 1.0;
    float b = 2.0;
    float c = foo(a, b);

    printf("c = %f\n", c);

    return 0;
}