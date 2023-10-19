#include <stdio.h>
#include <assert.h>
#include "converte.h"

void comparaArquivos(FILE *arquivo1, FILE *arquivo2){
    int ch1, ch2;
    while ((ch1 = fgetc(arquivo1)) != EOF && (ch2 = fgetc(arquivo2)) != EOF) {
        assert(ch1 == ch2);
    }
}

/*
Teste para verificar se a conversão de UTF-8 para varint está funcionando
Um caracterer codificado em UTF-8 é escrito em um arquivo, o mesmo caractere
é escrito em outro arquivo em varint, e então os dois arquivos são comparados
*/
void utf8VarintOneByte() {
    FILE *arquivoEntrada = fopen("utf2varint_entrada.txt", "wb");
    FILE *arquivoSaida = fopen("utf2varint_saida", "wb");

    if (arquivoEntrada == NULL) {
            printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
            return;
    }

    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_saida\n");
        return;
    }
    // Criando a sequência de bytes correspondente ao caractere © em UTF-8
    fputc(0x00A9, arquivoEntrada);

    fclose(arquivoEntrada);
    arquivoEntrada = fopen("utf2varint_entrada.txt", "rb");
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
        return;
    }

    utf2varint(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    arquivoEntrada = fopen("varint2utf_entrada", "wb");
    arquivoSaida = fopen("varint2utf_saida.txt", "wb");
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo varint2utf_entrada\n");
        return;
    }
    if(arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo varint2utf_saida.txt\n");
        return;
    }


    // Criando a sequência de bytes correspondente ao caractere © em varint
    unsigned char utf8_bytes[] = {0xC2, 0xA9};

    fwrite(utf8_bytes, sizeof(unsigned char), sizeof(utf8_bytes), arquivoEntrada);

    fclose(arquivoEntrada);
    arquivoEntrada = fopen("varint2utf_entrada", "rb");
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo varint2utf_entrada\n");
        return;
    }

    varint2utf(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    arquivoEntrada = fopen("utf2varint_entrada.txt", "rb");
    arquivoSaida = fopen("varint2utf_saida.txt", "rb");
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
        return;
    }
    if(arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo varint2utf_saida.txt\n");
        return;
    }

    // Comparando o conteúdo dos arquivos de entrada e resultado
    comparaArquivos(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Conversão de UTF-8 para varint: sucesso.\n");
}

int varintUtf8OneByte(){
    FILE *arquivoEntrada = fopen("varintUtf8_entrada.txt", "wb");
    FILE *arquivoSaida = fopen("varintUtf8_saida", "wb");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo varintUtf8_entrada.txt\n");
        return 1;
    }
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo varintUtf8_saida\n");
        return 1;
    }
    
    // Criando a sequência de bytes correspondente ao caractere © em varint
    unsigned char utf8_bytes[] = {0xC2, 0xA9};

    fwrite(utf8_bytes, sizeof(unsigned char), sizeof(utf8_bytes), arquivoEntrada);
    fclose(arquivoEntrada);

    fopen("varintUtf8_entrada.txt", "rb");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo varintUtf8_entrada.txt\n");
        return 1;
    }
    utf2varint(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    arquivoEntrada = fopen("utf2varint_entrada.txt", "wb");
    arquivoSaida = fopen("utf2varint_saida", "wb");
    if (arquivoEntrada == NULL) {
            printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
            return 1;
    }

    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_saida\n");
        return 1;
    }
    // Criando a sequência de bytes correspondente ao caractere © em UTF-8
    fputc(0x00A9, arquivoEntrada);

    fclose(arquivoEntrada);
    fopen("utf2varint_entrada.txt", "rb");
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
        return 1;
    }

    utf2varint(arquivoEntrada, arquivoSaida);
    fclose(arquivoEntrada);

    arquivoEntrada = fopen("varintUtf8_entrada.txt", "rb");
    arquivoSaida = fopen("utf2varint_saida", "rb");
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo utf2varint_entrada.txt\n");
        return 1;
    }
    if(arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo varint2utf_saida.txt\n");
        return 1;
    }

    // Comparando o conteúdo dos arquivos de entrada e resultado
    comparaArquivos(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Conversão de varint para UTF-8: sucesso.\n");

    return 0;
}

int main() {
    utf8VarintOneByte();
    varintUtf8OneByte();

    return 0;
}