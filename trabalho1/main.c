#include <stdio.h>
#include <stdlib.h>
#include "converte.h"

int main() {
    FILE *arq_entrada = fopen("utf8_peq.txt", "rb");
    FILE *arq_saida = fopen("arquivo_saida.txt", "wb");

    if (arq_entrada == NULL || arq_saida == NULL) {
    printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    utf2varint(arq_entrada, arq_saida);

    fclose(arq_entrada);
    fclose(arq_saida);

    return 0;
}