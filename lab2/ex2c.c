#include <ctype.h>
#include <stdio.h>

int string2num (char *s, int x) {
    int a = 0;
    for (; *s; s++){
        if(isdigit(*s))
            a = a*x + (*s - '0');
        else
            a = a*x + (*s - 'a' + 10);
    }
    return a;
}

int main (void) {
    printf("%d\n", string2num("777", 8));
    printf("%d\n", string2num("777", 10));
    return 0;
}
