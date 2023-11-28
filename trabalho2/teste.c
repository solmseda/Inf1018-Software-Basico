#include <stdio.h>
#include "cria_func.h"

typedef int (*func_ptr) (int x);

int mult(int x, int y, int z) {
return (x * y) + 1;
}

int main (void) {
    DescParam params[3];
    func_ptr f_mult;
    int i;
    unsigned char codigo[500];

    params[0].tipo_val = INT_PAR; /* o primeiro parãmetro de mult é int */
    params[0].orig_val = PARAM;   /* a nova função repassa seu parämetro */

    params[1].tipo_val = INT_PAR; /* o segundo parâmetro de mult é int */
    params[1].orig_val = FIX;     /* a nova função passa para mult a constante 10 */
    params[1].valor.v_int = 10;

    params[2].tipo_val = INT_PAR; /* o segundo parâmetro de mult é int */
    params[2].orig_val = FIX;     /* a nova função passa para mult a constante 10 */
    params[2].valor.v_int = 1;

    cria_func (mult, params, 2, codigo);
    f_mult = (func_ptr) codigo;   

    for (i = 1; i <=10; i++) {
    printf("%d\n", f_mult(i)); /* a nova função só recebe um argumento */
    }

    return 0;
}