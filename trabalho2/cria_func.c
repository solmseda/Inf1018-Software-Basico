/* Gabrielle Trajano Mulinari 1811897 3WA */
/* Sol Castilho Araújo de Moraes Sêda 1711600 3WA*/


#include "cria_func.h"
#include <stdio.h>
#include <stdlib.h>

void cria_func(void* f, DescParam params[], int n, unsigned char code[]) {
    int i = 0;
    int j;
    int cont = 0; // count the number of parameters
    int aux;
    int fixParams = 0; // count the number of fixed parameters

    // move instruction for the temporary register
    unsigned char reg[][3] = {{0xfa, 0xf8, 0xf9}, {0xf2, 0xf0, 0xf1}, {0xd2, 0xd0, 0xd1}};

    // registers for mov operations %r10d  %r8d  %r9d
    unsigned char regSave[] = {0xba, 0xb8, 0xb9};

    //                          %edi  %esi  %edx
    unsigned char regCall[] = {0xd7, 0xc6, 0xca};

    // array with instructions to save pointers
    unsigned char saveD[] = {0x12, 0x00, 0x09};

    // auxiliary variable used to get the value of int and the call
    union {
        int i;
        char c[4];
    } u;

    // auxiliary variable used to get the value of pointers
    union {
        unsigned long l;
        char c[8];
    } y;

    // pushq %rbp // movq  %rsp, %rbp
    code[i++] = 0x55;
    code[i++] = 0x48;
    code[i++] = 0x89;
    code[i++] = 0xe5;

    // move the parameter registers to save them
    // edi -> r10d
    // esi -> r8d
    // edx -> r9d
    for (j = 0; j < n; j++, cont++) {
        if (params[j].tipo_val == INT_PAR) {
            if (params[j].orig_val == PARAM) {
                // place the parameter in the correct register to call the function
                code[i++] = 0x41;
                code[i++] = 0x89;
                code[i++] = reg[cont][j];
            } else if (params[j].orig_val == FIX) {
                fixParams++;
                code[i] = 0x41;
                code[i + 1] = regSave[j];
                i += 2;
                u.i = params[j].valor.v_int;
                for (aux = 0; aux < 4; aux++) {
                    code[i] = u.c[aux];
                    i++;
                }
            } else if (params[j].orig_val == IND) {
                code[i] = 0x49;
                code[i + 1] = regSave[j];
                i += 2;

                y.l = (unsigned long) params[j].valor.v_ptr;
                for (aux = 0; aux < 8; aux++) {
                    code[i] = y.c[aux];
                    i++;
                }

                // mov (%r10), %r10d or other registers depending on the number of parameters
                code[i] = 0x45;
                code[i + 1] = 0x8b;
                code[i + 2] = saveD[j];
                i += 3;
            }
        } else if (params[j].tipo_val == PTR_PAR) {
            if (params[j].orig_val == PARAM) {
                code[i++] = 0x49;
                code[i++] = 0x89;
                code[i++] = reg[cont - fixParams][j];
            }
            if (params[j].orig_val == FIX || params[j].orig_val == IND) {
                if (params[j].orig_val == FIX) {
                    fixParams++;
                }
                code[i++] = 0x49;
                code[i++] = regSave[j];

                y.l = (unsigned long) params[j].valor.v_ptr;
                for (aux = 0; aux < 8; aux++) {
                    code[i++] = y.c[aux];
                }

                if (params[j].orig_val == IND) {
                    code[i++] = 0x49;
                    code[i++] = 0x8b;
                    code[i++] = saveD[j];
                }
            }
        }
    }

    // move to the parameter registers to call the function
    // r12-> rdi
    // r8 -> rsi
    // r9 -> rdx
    for (j = 0; j < n; j++) {
        if (params[j].tipo_val == INT_PAR)
            code[i] = 0x44;
        else
            code[i] = 0x4c;

        code[i + 1] = 0x89;
        i += 2;
        code[i] = regCall[j];
        i++;
    }

    // Move the address of the function f to the rax register
    code[i++] = 0x48; // REX prefix to indicate the use of extended register
    code[i++] = 0xb8; // Opcode for mov rax
    *((void**)(&code[i])) = f; // Address of the function f
    i += 8; // Move 8 bytes forward

    // Call rax
    code[i++] = 0xFF; 
    code[i++] = 0xD0; 

    // leave // ret
    code[i++] = 0xc9;
    code[i++] = 0xc3;
}