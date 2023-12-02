#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cria_func.h"

#include <string.h>

void inicializar_prologo(unsigned char codigo[], int *size) {
    // Instrução pushq %rbp
    codigo[0] = 0x55;

    // Instrução movq %rsp, %rbp
    codigo[1] = 0x48;
    codigo[2] = 0x89;
    codigo[3] = 0xe5;
    *size = 4;
}

void move_int_to_register(int valor, int i, unsigned char codigo[], int *index, int *tamanho_do_movimento_inteiro) {
    // Os opcodes para mover um valor para cada um dos registradores de parâmetros
    unsigned char opcodes[][2] = {{0xbf}, {0xbe}, {0xba}, {0xb9}, {0xb8}, {0x41, 0xb8}, {0x41, 0xb9}};

    if (i < 6) {
        // Definindo o tamanho do opcode
        int opcode_size = i < 4 ? 1 : 2;
        
        printf("Movendo valor %d para registrador %d\n", valor, i);
        
        // Adicione instruções de impressão para mostrar qual valor está sendo movido para qual registrador
        for (int j = 0; j < opcode_size; j++) {
            codigo[*index + j] = opcodes[i][j];
        }
        for (int j = 0; j < sizeof(valor); j++) {
            codigo[*index + opcode_size + j] = ((unsigned char *)&valor)[j];
        }
        *index += sizeof(valor) + opcode_size;

        // Definir o tamanho_do_movimento_inteiro
        *tamanho_do_movimento_inteiro = opcode_size + sizeof(valor);
    }
}


// Function to move a pointer value to the appropriate register
void move_ptr_to_register(void* ptr, int register_number, unsigned char* codigo, int* index) {
    // Check if the register number is valid
    if (register_number < 0 || register_number > 2) {
        fprintf(stderr, "Invalid register number: %d\n", register_number);
        exit(1);
    }

    // The opcodes for moving a value to rdi, rsi, and rdx respectively
    const unsigned char opcodes[] = {0xbf, 0xbe, 0xba};

    // Write the opcode to the code array
    codigo[*index] = 0x48; // REX prefix for 64-bit
    codigo[*index + 1] = opcodes[register_number]; // Opcode for mov to the register
    memcpy(&codigo[*index + 2], &ptr, sizeof(ptr)); // Copy the pointer
    *index += 2 + sizeof(ptr);
}



void chama_func_original(void *f, unsigned char codigo[], int *index) {
    // Instrução movq para mover o endereço da função para %rax
    codigo[*index] = 0x48;
    codigo[*index + 1] = 0xb8;
    for (int i = 0; i < sizeof(f); i++) {
        codigo[*index + 2 + i] = ((unsigned char *)&f)[i];
    }

    // Instrução call *%rax
    codigo[*index + 2 + sizeof(f)] = 0xff;
    codigo[*index + 3 + sizeof(f)] = 0xd0;

    *index += 4 + sizeof(f);
}

void clean_stack(int n, unsigned char codigo[]) {
    codigo[0] = 0x48; // Opcode movq
    codigo[1] = 0x83; // Opcode subq
    codigo[2] = 0xec; // Tamanho a subtrair da pilha
    codigo[3] = n * sizeof(int);
    codigo[4] = 0xc3; // Opcode retq
}

void finaliza_epilogo(unsigned char codigo[]) {
    codigo[0] = 0x5d; // Opcode popq %rbp
    codigo[1] = 0xc3; // Opcode retq
}

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    int index = 0;
    int tamanho_do_movimento_inteiro;
    int tamanho_do_movimento_ponteiro;
    int size;

    inicializar_prologo(codigo, &size);
    index += size;

    for (int i = 0; i < n; i++) {
        if (params[i].tipo_val == INT_PAR) {
            if (params[i].orig_val == FIX) {
                // Valor fixo - move diretamente para o registrador
                move_int_to_register(params[i].valor.v_int, i, codigo, &index, &tamanho_do_movimento_inteiro);
            }else if (params[i].orig_val == IND) {
                // Endereço de uma variável - move o endereço da variável para o registrador
                int *valor = params[i].valor.v_ptr;
                move_int_to_register(*valor, i, codigo, &index, &tamanho_do_movimento_inteiro);
            }
        }
        if (params[i].tipo_val == PTR_PAR) {
            if (params[i].orig_val == FIX) {
                // Fixed pointer value - move directly to the register
                move_ptr_to_register(params[i].valor.v_ptr, i % 3, codigo, &index);
            } else if (params[i].orig_val == IND) {
                // Address of a variable - move the address to the register
                void *valor = params[i].valor.v_ptr;
                move_ptr_to_register(valor, i % 3, codigo, &index);
            } else if (params[i].orig_val == PARAM) {
                // PARAM case for PTR_PAR - move the pointer value to the register
                move_ptr_to_register(params[i].valor.v_ptr, i % 3, codigo, &index);
            }
        }
    }

    chama_func_original(f, codigo, &index);

    clean_stack(n, codigo + index);

    finaliza_epilogo(codigo + index);
}
