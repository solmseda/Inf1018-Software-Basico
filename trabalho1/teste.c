#include <stdio.h>
#include <assert.h>
#include "converte.h"

int main() {
    // Crie arquivos de entrada e saída fictícios para testar as funções
    FILE *input_file = fopen("input.txt", "rb");
    FILE *output_file = fopen("output.txt", "wb");

    // Teste utf2varint
    assert(utf2varint(input_file, output_file) == 0);

    // Feche e reabra os arquivos para a função varint2utf
    fclose(input_file);
    fclose(output_file);

    input_file = fopen("output.txt", "rb");
    output_file = fopen("result.txt", "wb");

    // Teste varint2utf
    assert(varint2utf(input_file, output_file) == 0);

    // Feche os arquivos
    fclose(input_file);
    fclose(output_file);

    // Abra os arquivos de entrada e resultado para verificar a consistência dos dados
    input_file = fopen("input.txt", "rb");
    FILE *result_file = fopen("result.txt", "rb");

    // Compare o conteúdo dos arquivos de entrada e resultado
    int ch1, ch2;
    while ((ch1 = fgetc(input_file)) != EOF && (ch2 = fgetc(result_file)) != EOF) {
        assert(ch1 == ch2);
    }

    // Feche os arquivos de entrada e resultado
    fclose(input_file);
    fclose(result_file);

    printf("Testes unitários concluídos com sucesso.\n");

    return 0;
}