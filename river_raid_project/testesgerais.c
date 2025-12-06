#include <stdio.h>

FILE* CriaMapa(char arquivoMapa[16]) {

    FILE* fp = fopen(arquivoMapa, "r");

    if (fp != NULL) {
        return fp;
    }

    return NULL;
}

int main(void) {

    FILE* mapa = CriaMapa("./maps/mapa1.txt");

    if (mapa == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    printf("Arquivo aberto com sucesso!\n");

    fclose(mapa); // <-- IMPORTANTE

    return 0;
}

