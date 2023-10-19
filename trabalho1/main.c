#include <stdio.h>
#include <stdlib.h>
#include "converte.h"

int main() {
    FILE *arq_entrada_utf8 = fopen("utf8_peq.txt", "rb");
    FILE *arq_saida_varint = fopen("utf2varint_saida.txt", "wb");

    utf2varint(arq_entrada_utf8, arq_saida_varint);

    fclose(arq_entrada_utf8);
    fclose(arq_saida_varint);

    FILE *arq_entrada_varint = fopen("var_peq", "rb");
    FILE *arq_saida_utf8 = fopen("varint2utf_saida.txt", "wb");

    varint2utf(arq_entrada_varint, arq_saida_utf8);

    fclose(arq_entrada_varint);
    fclose(arq_saida_utf8);

    return 0;
}