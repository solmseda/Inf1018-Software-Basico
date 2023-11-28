#ifndef CRIA_FUNC_H
#define CRIA_FUNC_H

typedef enum {INT_PAR, PTR_PAR} TipoValor;
typedef enum {PARAM, FIX, IND} OrigemValor;

typedef struct {
   TipoValor    tipo_val;  /* indica o tipo do parametro */
   OrigemValor  orig_val;  /* indica a origem do valor do parametro */
   union {
     int v_int;
     void* v_ptr;
   } valor;         /* define o valor ou endereÃ§o do parametro (amarrado) */
} DescParam;

/**
 * @brief Esta função gera código para chamar uma função fornecida.
 *
 * @param f O endereço da função original a ser chamada pelo código gerado.
 * @param params Um array contendo a descrição dos parâmetros para chamar esta função.
 * @param n O número de parâmetros descritos por params.
 * @param codigo Um vetor onde o código gerado será escrito.
 */
void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]);

#endif
