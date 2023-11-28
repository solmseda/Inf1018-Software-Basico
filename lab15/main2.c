#include<stdio.h>
#include<math.h>

float foo1 (float a, float b);

int main(){
    float a = foo1(M_PI, M_PI_2);

    printf("sin(Pi) + Pi/2 = %f\n", a);

    return 0;
}