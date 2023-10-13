#include <stdio.h>

/*
Identifica a quantidade de bytes que o  caractere tem, a partir da representação
dele em UTF-8
*/
int DeterminaQuantByte(int caractere) {
  if (caractere >= 0x00 && caractere <= 0x7F) {
    return 1;
  } else if (caractere >= 0x80 && caractere <= 0x7FF) {
    return 2;
  } else if (caractere >= 0x800 && caractere <= 0xFFFF) {
    return 3;
  } else if (caractere >= 0x10000 && caractere <= 0x10FFFF) {
    return 4;
  } else {
    return -1;
  }
}


int utf2varint(FILE *arq_entrada, FILE *arq_saida) {
    int character = 0;
    int numBytes = 0;
    int varInt = 0;

    while ((character = fgetc(arq_entrada)) != EOF) {
        numBytes = DeterminaQuantByte(character);

        for (int i = 0; i < numBytes; i++) {
            int byte = (character >> (6 * (numBytes - 1 - i))) & 0x3F;
            if (i != numBytes - 1) {
                byte |= 0x80;
            }
            varInt = (varInt << 8) | byte;
        }

        if (fwrite(&varInt, 1, numBytes, arq_saida) != numBytes) {
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
Conta a quantidada de bytes no varint
*/
int contaBytes(int varint) {
    int byte_count = 0;

    while (varint & 0x80) {
        byte_count++;
        varint >>= 7;
    }
    byte_count++;

    return byte_count;
}

/*
Constroi o UTF-8 a partir do varint
*/
void constroiUtf8(int varint, int *caractere) {
    int byte_count = contaBytes(varint);

    if (byte_count == 1) {
        *caractere = varint;
    } else {
        *caractere = (0x80 | (varint & 0x7F));
        for (int i = 1; i < byte_count; i++) {
            *caractere <<= 8;
            *caractere |= 0x80 | (varint >> (7 * i) & 0x7F);
        }
    }
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida) {
    int varint = 0;
    int caractere;

    while (fread(&varint, sizeof(int), 1, arq_entrada) == 1) {
      constroiUtf8(varint, &caractere);

      fwrite(&caractere, sizeof(int), 1, arq_saida);
    }

    if (ferror(arq_entrada)) {
        fprintf(stderr, "Erro de leitura no arquivo de entrada.\n");
        return -1;
    }

    return 0;
}