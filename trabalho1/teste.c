#include <stdio.h>
#include <assert.h>
#include "converte.h"

int main() {
    // Crie arquivos de entrada e saída fictícios para testar as funções
    FILE *input_file = fopen("utf2varint_entrada.txt", "wb");
    FILE *output_file = fopen("utf2varint_entrada", "wb");

    if (input_file == NULL) {
            printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
            return 1;
    }

    if (output_file == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada\n");
        return 1;
    }
    fputc(0x00A9, input_file);

    fclose(input_file);
    input_file = fopen("utf2varint_entrada.txt", "rb");

    // Teste utf2varint
    utf2varint(input_file, output_file);

    // Feche e reabra os arquivos para a função varint2utf
    fclose(input_file);
    fclose(output_file);

    input_file = fopen("varint2utf_entrada", "wb");
    output_file = fopen("varint2utf_saida.txt", "wb");


    // Crie a sequência de bytes correspondente ao caractere © em UTF-8
    unsigned char utf8_bytes[] = {0xC2, 0xA9};

    // Escreva a sequência de bytes no arquivo
    fwrite(utf8_bytes, sizeof(unsigned char), sizeof(utf8_bytes), input_file);

    fclose(input_file);
    input_file = fopen("varint2utf_entrada", "rb");
    

    // Teste varint2utf
    varint2utf(input_file, output_file);

    // Feche os arquivos
    fclose(input_file);
    fclose(output_file);

    // Abra os arquivos de entrada e resultado para verificar a consistência dos dados
    input_file = fopen("utf2varint_entrada.txt", "rb");
    output_file = fopen("varint2utf_saida.txt", "rb");

    // Compare o conteúdo dos arquivos de entrada e resultado
    int ch1, ch2;
    while ((ch1 = fgetc(input_file)) != EOF && (ch2 = fgetc(output_file)) != EOF) {
        assert(ch1 == ch2);
    }

    // Feche os arquivos de entrada e resultado
    fclose(input_file);
    fclose(output_file);

    printf("Testes unitários concluídos com sucesso.\n");

    return 0;
}