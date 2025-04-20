#include "tp.h"

int N, M;
int **tabuleiro;
int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, -1, 1};

int dentro_limites(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

void copiar_tabuleiro(int **dest, int **src, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            dest[i][j] = src[i][j];
}

int **alocar_tabuleiro(int linhas, int colunas) {
    int **tab = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        tab[i] = malloc(colunas * sizeof(int));
    }
    return tab;
}

void liberar_tabuleiro(int **tab, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(tab[i]);
    }
    free(tab);
}


void imprimir_tempos(struct rusage *inicio, struct rusage *fim) {
    long segundos_usuario = fim->ru_utime.tv_sec - inicio->ru_utime.tv_sec;
    long microssegundos_usuario = fim->ru_utime.tv_usec - inicio->ru_utime.tv_usec;

    long segundos_sistema = fim->ru_stime.tv_sec - inicio->ru_stime.tv_sec;
    long microssegundos_sistema = fim->ru_stime.tv_usec - inicio->ru_stime.tv_usec;

    double tempo_usuario = segundos_usuario + microssegundos_usuario / 1e6;
    double tempo_sistema = segundos_sistema + microssegundos_sistema / 1e6;

    printf("Tempo de usuário: %.6f segundos\n", tempo_usuario);
    printf("Tempo de sistema: %.6f segundos\n", tempo_sistema);
}
