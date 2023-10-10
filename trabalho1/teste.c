#include <stdio.h>
#include "converte.h"   
#include <stdio.h>


// Função de teste para o caso de sucesso
void teste_sucesso() {
    FILE *arq_entrada_sucesso = fopen("utf8_peq.txt", "rb");
    FILE *arq_saida_sucesso = fopen("arquivo_saida_sucesso.txt", "wb");

    if (arq_entrada_sucesso == NULL || arq_saida_sucesso == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de teste.\n");
        return;
    }

    printf("Teste de sucesso:\n");
    int resultado_sucesso = utf2varint(arq_entrada_sucesso, arq_saida_sucesso);
    if (resultado_sucesso == 0) {
        printf("Conversão bem-sucedida.\n");
    } else {
        printf("Erro na conversão.\n");
    }

    fclose(arq_entrada_sucesso);
    fclose(arq_saida_sucesso);
}

// Função de teste para arquivo de entrada inexistente
void teste_arquivo_inexistente() {
    FILE *arq_entrada_inexistente = fopen("arquivo_inexistente.txt", "rb");
    FILE *arq_saida_inexistente = fopen("arquivo_saida_inexistente.txt", "wb");

    if (arq_entrada_inexistente == NULL || arq_saida_inexistente == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de teste de erro.\n");
        return;
    }

    printf("\nTeste de erro (arquivo de entrada inexistente):\n");
    int resultado_inexistente = utf2varint(arq_entrada_inexistente, arq_saida_inexistente);
    if (resultado_inexistente == -1) {
        printf("Erro esperado: arquivo de entrada inexistente.\n");
    } else {
        printf("Erro inesperado.\n");
    }

    fclose(arq_entrada_inexistente);
    fclose(arq_saida_inexistente);
}

// Função de teste para arquivo de saída sem permissão de escrita
void teste_arquivo_sem_permissao() {
    FILE *arq_entrada_erro = fopen("arquivo_entrada_erro.txt", "rb");
    FILE *arq_saida_erro = fopen("/arquivo_saida_erro.txt", "wb");

    if (arq_entrada_erro == NULL || arq_saida_erro == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos de teste de erro.\n");
        return;
    }

    printf("\nTeste de erro (arquivo de saída sem permissão de escrita):\n");
    int resultado_erro = utf2varint(arq_entrada_erro, arq_saida_erro);
    if (resultado_erro == -1) {
        printf("Erro esperado: arquivo de saída sem permissão de escrita.\n");
    } else {
        printf("Erro inesperado.\n");
    }

    fclose(arq_entrada_erro);
    fclose(arq_saida_erro);
}

int main() {
    teste_sucesso();
    teste_arquivo_inexistente();
    teste_arquivo_sem_permissao();

    return 0;
}
