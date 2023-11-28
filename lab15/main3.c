#include<stdio.h>
#include<math.h>

float foo2 (float a, float b);

int main(){
    printf("sin(Pi) + cos(Pi) = %f\n", foo2(M_PI, M_PI));

    return 0;
}