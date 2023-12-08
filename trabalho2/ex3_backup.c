








#include "cria_func.h"
#include <stdio.h>
#include <stdlib.h>



void cria_func (void* f, DescParam params[], int n, unsigned char codigo[])
{
    //auxiliar usado para pegar o valor do int e da chamada do call 
    union {
        int i;
        char c[4];
    }u;

    //auxiliar usado para pegar o valor dos ponteiros
    union {
        unsigned long l;
        char c[8];
    }y;

    //função movl do para o registrador temporario                          
    unsigned char reg[][3] = {{0xfa, 0xf8, 0xf9}, {0xf2, 0xf0, 0xf1}, {0xd2, 0xd0, 0xd1}} ; 
    
    //registradores para fazer mov
    //                        %r10d  %r8d  %r9d
    unsigned char regSave[] = {0xba, 0xb8, 0xb9 }; 

    //                          %edi  %esi  %edx
    unsigned char regCall[] = {0xd7, 0xc6, 0xca}; 

    //vetor com instruções para salvar os ponteiros
    unsigned char saveD[] = {0x12, 0x00, 0x09}; 

    int i = 0;
    int j;
    int cont =0;
    int aux;

    //pushq %rbp //movq  %rsp, %rbp
    codigo[i++] = 0x55;
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;

    //move os registradores dos paramentros para salva-los 
    //edi ->  r10d
    //esi ->  r8d
    //edx ->  r9d
    int testeFix = 0;
   for( j = 0 ; j < n ; j++, cont++){
        if(params[j].tipo_val == INT_PAR){

            if(params[j].orig_val == PARAM){
                //coloca o parametro no registrador certo para chamar a funcao
                codigo[i] = 0x41;
                codigo[i+1] = 0x89;
                codigo[i+2] = reg[cont][j];
                i+=3;
                
            }
            else if (params[j].orig_val == FIX){
                codigo[i] = 0x41;
                codigo[i+1] = regSave[j];
                i+=2;
                u.i = params[j].valor.v_int;
                for(aux =0; aux < 4 ; aux++){
                    codigo[i] = u.c[aux];
                    i++; 
                }
                
            } 
            else if(params[j].orig_val == IND){

                codigo[i] = 0x49;
                codigo[i+1] = regSave[j];
                i+=2;

                y.l = (unsigned long) params[j].valor.v_ptr;
                for (aux = 0; aux<8; aux++){
                    codigo[i] = y.c[aux];
                    i++;
                }
                
                //mov (%r10), %r10d ou os outros registradores dependendo do num de parametro
                codigo[i] = 0x45; 
                codigo[i+1] = 0x8b;
                codigo[i+2] = saveD[j];
                i+=3;
                    
            }
        
        }
        else if(params[j].tipo_val == PTR_PAR) {
            if (params[j].orig_val == PARAM){
                codigo[i++] = 0x49;
                codigo[i++] = 0x89;
                codigo[i++] = reg[cont-testeFix][j];
            } 
            if(params[j].orig_val == FIX || params[j].orig_val == IND) {
                if (params[j].orig_val == FIX ){
                    testeFix++;
                }
                codigo[i++] = 0x49;
                codigo[i++] = regSave[j];

                y.l = (unsigned long) params[j].valor.v_ptr;
                for (aux = 0; aux < 8; aux++) {
                    codigo[i++] = y.c[aux];
                }

                if(params[j].orig_val == IND) {
                    codigo[i++] = 0x49;
                    codigo[i++] = 0x8b;
                    codigo[i++] = saveD[j];
                }
            }
        }

    }

    //move para os registradores de parametros para chamar a funcao;
    //r12-> rdi
    //r8 -> rsi  
    //r9 -> rdx 
    for( j = 0 ; j < n ; j++){
        if(params[j].tipo_val == INT_PAR)
            codigo[i] = 0x44 ;
        else 
            codigo[i] = 0x4c ;

        codigo[i+1] = 0x89 ;
        i+=2;
        codigo[i] = regCall[j];
        i++;
    }    

    // Move o endereço da função f para o registrador rax
    codigo[i++] = 0x48; // REX prefixo para indicar uso de registrador estendido
    codigo[i++] = 0xb8; // Opcode para mov rax, imm64
    *((void**)(&codigo[i])) = f; // Endereço da função f
    i += 8; // Avança 8 bytes

    // Faz call rax
    codigo[i++] = 0xFF; // Opcode para call r/m64
    codigo[i++] = 0xD0; // ModR/M byte para call rax

    //leave //ret
    codigo[i++] = 0xc9;
    codigo[i++] = 0xc3;

    printf("código de maquina gerado:\n");
    for (int idx = 0; idx < i; ++idx) {
        printf("%02X ", codigo[idx]);
    }
    printf("\n");

}