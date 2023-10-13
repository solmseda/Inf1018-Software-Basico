#include <stdio.h>
#include <stdlib.h>
#include "converte.h"

int main() {
    FILE *arq_entrada_utf8 = fopen("utf8_peq.txt", "rb");
    FILE *arq_saida_varint = fopen("arquivo_saida_varint", "wb");
    FILE *arq_entrada_varint = fopen("var_peq", "rb");
    FILE *arq_saida_utf8 = fopen("arquivo_saida_utf8.txt", "wb");

    if (arq_entrada_utf8 == NULL || arq_saida_varint == NULL || arq_entrada_varint == NULL ||arq_saida_utf8 == NULL) {
    printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    utf2varint(arq_entrada_utf8, arq_saida_varint);
    varint2utf(arq_entrada_varint, arq_saida_utf8);

    fclose(arq_entrada_utf8);
    fclose(arq_saida_varint);
    fclose(arq_entrada_varint);
    fclose(arq_saida_utf8);

    return 0;
}