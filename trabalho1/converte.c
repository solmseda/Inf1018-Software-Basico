/*
Gabrielle Trajano Mulinari – 1811897 – 3WA
Sol Castilho Araújo de Moraes Sêda – 1711600 – 3WA
*/

#include <stdio.h>

/*
Identifica a quantidade de bytes que o caractere tem, a partir da representação
dele em UTF-8
*/
int DeterminaQuantByte(int caractere) {
  if (caractere >= 0x00 && caractere <= 0x7F) {                 // Se o caractere está dentro do primeiro intervalo
    return 1;
  } else if (caractere >= 0x80 && caractere <= 0x7FF) {         // Se o caractere está dentro do segundo intervalo
    return 2;
} else if (caractere >= 0x800 && caractere <= 0xFFFF) {         // Se o caractere está dentro do terceiro intervalo
    return 3; 
  } else if (caractere >= 0x10000 && caractere <= 0x10FFFF) {   // Se o caractere está dentro do quarto intervalo
    return 4;
  } else {
    return -1;
  }
}

int utf2varint(FILE *arq_entrada, FILE *arq_saida) {
    int character = 0;
    int numBytes = 0;
    int varint = 0;

    while ((character = fgetc(arq_entrada)) != EOF) {
        numBytes = DeterminaQuantByte(character);                       // Determina o número de bytes do caractere.

        for (int i = 0; i < numBytes; i++) {
            int byte = (character >> (6 * (numBytes - 1 - i))) & 0x3F;  // Extrai os bits do caractere em grupos de 6 bits.
            if (i != numBytes - 1) {
                byte |= 0x80;                                           // Define o bit de continuação como 1 em todos os bytes, exceto o último.
            }
            varint = (varint << 8) | byte;                              // Adiciona o byte ao varint.
        }

        if (fwrite(&varint, 1, numBytes, arq_saida) != numBytes) {      // Escreve o varint no arquivo de saída.
            fprintf(stderr, "Erro de gravação\n");
            return -1;
        }
    }

    if (ferror(arq_entrada)) {
        fprintf(stderr, "Erro de leitura\n");
        return -1;
    }

    return 0;
}

/*
Conta a quantidade de bytes no varint
*/
int contaBytes(int varint) {
    int byte_count = 0;             // Inicializa a contagem de bytes em 0

    while (varint & 0x80) {         // Enquanto o bit mais significativo for 1
        byte_count++;               // Incrementa a contagem de bytes
        varint >>= 7;               // Desloca 7 bits para a direita
    }
    byte_count++;                   // Incrementa a contagem de bytes uma vez mais para o último byte

    return byte_count;              // Retorna o número total de bytes necessários para representar o varint
}

/*
Constroi o UTF-8 a partir do varint
*/
void constroiUtf8(int varint, int *caractere) {
    int byte_count = contaBytes(varint);                        // Calcula a quantidade de bytes necessários

    if (byte_count == 1) {                                      // Verifica se o varint cabe em um único byte
        *caractere = varint;                                    // Atribui o valor do varint ao caractere
    } else {
        *caractere = (0x80 | (varint & 0x7F));                  // Escreve o primeiro byte com os bits do varint
        for (int i = 1; i < byte_count; i++) {
            *caractere <<= 8;                                   // Desloca o caractere 8 bits para a esquerda para dar espaço para o próximo byte
            *caractere |= 0x80 | (varint >> (7 * i) & 0x7F);    // Preenche os bytes restantes com os bits do varint
        }
    }
}

/*
Escreve um valor UTF-8 no arquivo de saída
*/
void escreveUtf8(int valor, FILE *arq_saida) {
    unsigned char caractere[5] = {0};                               // Inicializa um array de caracteres para armazenar o valor UTF-8
    int i;
    for (i = 0; valor > 0x7F; i++) {
        caractere[i] = (valor & 0x7F) | 0x80;                       // Armazena o byte atual com o bit mais significativo definido
        valor >>= 7;                                                // Desloca o valor 7 bits para a direita
    }
    caractere[i] = valor;                                           // Armazena o último byte
    fwrite(caractere, sizeof(unsigned char), i + 1, arq_saida);     // Escreve os bytes no arquivo de saída
}

/*
Converte varints em UTF-8 e escreve no arquivo de saída
*/
void varint2utf(FILE *arq_entrada, FILE *arq_saida) {
    int c;
    int valor = 0;
    int shift = 0;

    while ((c = fgetc(arq_entrada)) != EOF) {               // Lê caracteres do arquivo de entrada até o fim do arquivo (EOF)
        valor |= (c & 0x7F) << shift;                       // Acumula os bits lidos no valor varint e ajusta o deslocamento
        shift += 7;                                         // Atualiza o deslocamento para o próximo byte
        if ((c & 0x80) == 0) {                              // Se o bit mais significativo de c for 0, o varint atual foi lido completamente
            escreveUtf8(valor, arq_saida);                  // Escreve o valor UTF-8 no arquivo de saída
            valor = 0;                                      // Zera o valor para o próximo varint
            shift = 0;                                      // Zera o deslocamento
        }
    }
}