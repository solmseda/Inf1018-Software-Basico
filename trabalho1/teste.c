#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "converte.h"

void comparaArquivos(FILE *arquivo1, FILE *arquivo2) {
    int ch1, ch2;
    int diferenca = 0;

    while ((ch1 = fgetc(arquivo1)) != EOF && (ch2 = fgetc(arquivo2)) != EOF) {
        if (ch1 != ch2) {
            diferenca = 1;
            break;
        }
    }

    if (diferenca) {
        printf("Os arquivos são diferentes.\n");
    } else {
        printf("Os arquivos são iguais.\n");
    }
}

void utf8VarintOneByte(const char *utf8_bytes, const char *varint_bytes) {
    FILE *arquivoEntrada = fopen("utf2varint_entrada.txt", "wb");
    FILE *arquivoSaida = fopen("utf2varint_saida", "wb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    size_t entradaLength = strlen(utf8_bytes);
    fwrite(utf8_bytes, 1, entradaLength, arquivoEntrada);
    fclose(arquivoEntrada);

    arquivoEntrada = fopen("utf2varint_entrada.txt", "rb");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
        return;
    }

    utf2varint(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    arquivoEntrada = fopen("varintUtf8_entrada", "wb");
    arquivoSaida = fopen("varintUtf8_saida.txt", "wb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    size_t saidaEsperadaLength = strlen(varint_bytes);
    fwrite(varint_bytes, 1, saidaEsperadaLength, arquivoEntrada);
    fclose(arquivoEntrada);

    arquivoEntrada = fopen("varintUtf8_entrada", "rb");
    arquivoSaida = fopen("varintUtf8_saida.txt", "rb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    varint2utf(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    arquivoEntrada = fopen("utf2varint_entrada.txt", "rb");
    arquivoSaida = fopen("varintUtf8_saida.txt", "rb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    comparaArquivos(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Conversão de UTF-8 para varint: sucesso.\n");
}

void varintUtf8OneByte(const char *varint_bytes, const char *utf8_bytes) {
    FILE *arquivoEntrada = fopen("varintUtf8_entrada", "wb");
    FILE *arquivoSaida = fopen("varintUtf8_saida.txt", "wb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    size_t entradaLength = strlen(varint_bytes);
    fwrite(varint_bytes, 1, entradaLength, arquivoEntrada);
    fclose(arquivoEntrada);

    arquivoEntrada = fopen("varintUtf8_entrada", "rb");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo varintUtf8_entrada\n");
        return;
    }

    utf2varint(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    arquivoEntrada = fopen("utf2varint_entrada.txt", "wb");
    arquivoSaida = fopen("utf2varint_saida", "wb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    size_t saidaEsperadaLength = strlen(utf8_bytes);
    fwrite(utf8_bytes, 1, saidaEsperadaLength, arquivoEntrada);
    fclose(arquivoEntrada);

    arquivoEntrada = fopen("utf2varint_entrada.txt", "rb");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
        return;
    }

    utf2varint(arquivoEntrada, arquivoSaida);
    fclose(arquivoEntrada);

    arquivoEntrada = fopen("varintUtf8_entrada", "rb");
    arquivoSaida = fopen("utf2varint_saida", "rb");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos de entrada/saída\n");
        return;
    }

    comparaArquivos(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Conversão de varint para UTF-8: sucesso.\n");
}


int main() {
    printf("Para testar a conversão de UTF-8 para varint e de varint para UTF-8 utilizando um byte\n");
    char utf8_bytes1[] = {'\0'};
    char varint_bytes1[] = {0x00};

    utf8VarintOneByte(utf8_bytes1, varint_bytes1);
    varintUtf8OneByte(varint_bytes1, utf8_bytes1);

    printf("Para testar a conversão de UTF-8 para varint e de varint para UTF-8 utilizando dois bytes\n");
    char utf8_bytes2[] = {0xC2, 0x2F};
    char varint_bytes2[] = {0x2F};

    utf8VarintOneByte(utf8_bytes2, varint_bytes2);
    varintUtf8OneByte(varint_bytes2, utf8_bytes2);

    printf("Para testar a conversão de UTF-8 para varint e de varint para UTF-8 utilizando três bytes\n");
    char utf8_bytes3[] = {0xE2, 0x82, 0xAC};
    char varint_bytes3[] = {0xAC};

    utf8VarintOneByte(utf8_bytes3, varint_bytes3);
    varintUtf8OneByte(varint_bytes3, utf8_bytes3);

    printf("Para testar a conversão de UTF-8 para varint e de varint para UTF-8 utilizando quatro bytes\n");
    char utf8_bytes4[] = {0xF0, 0x9F, 0x92, 0xA9};
    char varint_bytes4[] = {0x92, 0x4A, 0x8F};

    utf8VarintOneByte(utf8_bytes4, varint_bytes4);
    varintUtf8OneByte(varint_bytes4, utf8_bytes4); 

    return 0;
}
