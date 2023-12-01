#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cria_func.h"

#include <string.h>

// Os opcodes para mover um valor para cada um dos registradores de parâmetros
const unsigned char opcodes[][2] = {{0xbf}, {0xbe}, {0xba}, {0xb9}, {0xb8}, {0x41, 0xb8}, {0x41, 0xb9}};


/// @brief Initializes the prologue of the assembly code. Writes the instructions to push the base pointer onto the stack and move the stack pointer to the base pointer.
/// @param codigo The array to write the assembly code to.
/// @param size A pointer to an integer to store the size of the prologue.
void inicializar_prologo(unsigned char codigo[], int *size) {
    // Instrução pushq %rbp
    codigo[0] = 0x55;

    // Instrução movq %rsp, %rbp
    codigo[1] = 0x48;
    codigo[2] = 0x89;
    codigo[3] = 0xe5;
    *size = 4;
}

/// @brief Moves an integer value to a register. Writes the opcode for the move instruction and the integer value to the code array.
/// @param valor The integer value to move to the register.
/// @param i The index of the register to move the value to.
/// @param codigo The array to write the assembly code to.
/// @param index A pointer to the current index in the code array.
/// @param tamanho_do_movimento_inteiro A pointer to an integer to store the size of the move instruction.
void move_int_to_register(int valor, int i, unsigned char codigo[], int *index, int *tamanho_do_movimento_inteiro) {
    printf("Valor: %d\n", valor);
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

/// @brief Moves an address to a register. Writes the opcode for the move instruction and the address to the code array.
/// @param address The address to move to the register.
/// @param register_number The number of the register to move the address to.
/// @param codigo The array to write the assembly code to.
/// @param index A pointer to the current index in the code array.
void move_address_to_register(void* address, int register_number, unsigned char* codigo, int* index) {
    // Check if the register number is valid
    if (register_number < 0 || register_number >= sizeof(opcodes) / sizeof(opcodes[0])) {
        fprintf(stderr, "Invalid register number: %d\n", register_number);
        exit(1);
    }

    // Get the opcode for the register
    const unsigned char* opcode = opcodes[register_number];

    // Write the opcode to the code array
    for (int i = 0; i < sizeof(opcodes[0]); i++) {
        if (opcode[i] != 0) {
            codigo[*index] = opcode[i];
            (*index)++;
        }
    }

    // Write the address to the code array
    *(void**)(codigo + *index) = address;
    *index += sizeof(void*);
    printf("Assembly code on move_address_to_register: ");
    for (int i = 0; i < *index; i++) {
        printf("%02X ", codigo[i]);
    }
    printf("\n");
}

void dereference_pointer_in_register(int register_number, unsigned char* codigo, int* index) {
    // Check if the register number is valid
    if (register_number < 0 || register_number > 7) {
        fprintf(stderr, "Invalid register number: %d\n", register_number);
        exit(1);
    }

    // Write the opcode for the MOV instruction to the code array
    // The opcode is 0x48 0x8B followed by the register number
    codigo[*index] = 0x48;
    codigo[*index + 1] = 0x8B;
    codigo[*index + 2] = 0x00 | (register_number << 3);
    *index += 3;

    printf("Assembly code dereference_pointer_in_register: ");
    for (int i = 0; i < *index; i++) {
        printf("%02X ", codigo[i]);
    }
    printf("\n");
}

/// @brief Dereferences a pointer in a register. Writes the opcode for the MOV instruction to the code array.
/// @param register_number The number of the register that contains the pointer to dereference.
/// @param codigo The array to write the assembly code to.
/// @param index A pointer to the current index in the code array.
void call_original_function(void *f, unsigned char codigo[], int *index, int num_params, DescParam params[]) {
    codigo[*index + 1] = 0xe8; // Opcode callq
    long offset = (unsigned char*)&f - codigo - *index;
    
    //converte o endereço para litle endian
    for (int i = 1; i < 4; i++) {
        codigo[*index + i] = (offset >> (i * 8)) & 0xFF;
    }
}

/// @brief Cleans the stack after the function call. Subtracts the size of the parameters from the stack pointer.
/// @param n The number of parameters.
/// @param codigo The array to write the assembly code to.
void clean_stack(int n, unsigned char codigo[]) {
    codigo[0] = 0x48; // Opcode movq
    codigo[1] = 0x83; // Opcode subq
    codigo[2] = 0xec; // Tamanho a subtrair da pilha
    codigo[3] = n * sizeof(int);
    codigo[4] = 0xc3; // Opcode retq
}

/// @brief Finalizes the epilogue of the assembly code. Writes the instructions to pop the base pointer from the stack and return from the function.
/// @param codigo The array to write the assembly code to.
void finaliza_epilogo(unsigned char codigo[]) {
    codigo[0] = 0x5d; // Opcode popq %rbp
    codigo[1] = 0xc3; // Opcode retq
}

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    int index = 0;
    int tamanho_do_movimento_inteiro;
    int size;

    inicializar_prologo(codigo, &size);
    index += size;

    for (int h = 0; h < n; h++) {
        if (params[h].tipo_val == INT_PAR) {
            if (params[h].orig_val == FIX) {
                // Valor fixo - move diretamente para o registrador
                move_int_to_register(params[h].valor.v_int, h, codigo, &index, &tamanho_do_movimento_inteiro);
            }
            else if (params[h].orig_val == IND) {
                // Endereço de uma variável - move o endereço da variável para o registrador
                move_address_to_register(params[h].valor.v_ptr, h, codigo, &index);
                // Dereference the pointer in the register to get the value of the variable
                dereference_pointer_in_register(h, codigo, &index);
            }
        }
    }

    call_original_function(f, codigo, &index, n, params);

    clean_stack(n, codigo + index);

    finaliza_epilogo(codigo + index);
}
