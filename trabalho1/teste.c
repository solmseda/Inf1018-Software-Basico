#include <stdio.h>
#include "converte.h"   
#include <stdio.h>
// Função para verificar a conversão e correspondência dos arquivos
int verificarCorrespondencia(const char *arquivoEntradaUTF8, const char *arquivoEntradaVarint, const char *arquivoSaidaUTF8, const char *arquivoSaidaVarint) {
    FILE *arq_entrada_utf8 = fopen(arquivoEntradaUTF8, "rb");
    FILE *arq_entrada_varint = fopen(arquivoEntradaVarint, "rb");

    if (arq_entrada_utf8 == NULL || arq_entrada_varint == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de entrada.\n");
        return -1;
    }

    FILE *arq_saida_utf8 = fopen(arquivoSaidaUTF8, "wb");
    FILE *arq_saida_varint = fopen(arquivoSaidaVarint, "wb");

    if (arq_saida_utf8 == NULL || arq_saida_varint == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de saída.\n");
        fclose(arq_entrada_utf8);
        fclose(arq_entrada_varint);
        return -1;
    }

    int resultado_utf8_varint = utf2varint(arq_entrada_utf8, arq_saida_varint);
    int resultado_varint_utf8 = varint2utf(arq_entrada_varint, arq_saida_utf8);

    fclose(arq_entrada_utf8);
    fclose(arq_entrada_varint);
    fclose(arq_saida_utf8);
    fclose(arq_saida_varint);

    if (resultado_utf8_varint == 0 && resultado_varint_utf8 == 0) {
        // Ambas as conversões foram bem-sucedidas
        return 0;
    } else {
        fprintf(stderr, "Erro na conversão.\n");
        return -1;
    }
}

int compararArquivos(const char *arquivo1, const char *arquivo2) {
    FILE *file1 = fopen(arquivo1, "rb");
    FILE *file2 = fopen(arquivo2, "rb");

    if (file1 == NULL || file2 == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos para comparação.\n");
        return -1;
    }

    int caracter1, caracter2;
    int erro = 0;

    while (1) {
        caracter1 = fgetc(file1);
        caracter2 = fgetc(file2);

        if (caracter1 != caracter2) {
            erro = 1;
            break;
        }

        if (caracter1 == EOF || caracter2 == EOF) {
            break;
        }
    }

    fclose(file1);
    fclose(file2);

    if (erro) {
        fprintf(stderr, "Os arquivos não correspondem.\n");
        return -1;
    } else {
        return 0;
    }
}

int main() {
    const char *arquivoEntradaUTF8 = "arquivo_original_utf8.txt";
    const char *arquivoEntradaVarint = "arquivo_original_varint.bin";
    const char *arquivoSaidaUTF8 = "arquivo_saida_utf8.txt";
    const char *arquivoSaidaVarint = "arquivo_saida_varint.bin";

    if (verificarCorrespondencia(arquivoEntradaUTF8, arquivoEntradaVarint, arquivoSaidaUTF8, arquivoSaidaVarint) == 0) {
        printf("As conversões correspondem aos arquivos originais.\n");
    } else {
        printf("As conversões não correspondem aos arquivos originais.\n");
    }

    if (compararArquivos(arquivoEntradaUTF8, arquivoSaidaUTF8) == 0 && compararArquivos(arquivoEntradaVarint, arquivoSaidaVarint) == 0) {
        printf("Os arquivos correspondem corretamente.\n");
    }

    return 0;
}