#include "tp.h"

int N, M;
int tabuleiro[MAX_N][MAX_M];
int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, -1, 1};

int dentro_limites(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

void copiar_tabuleiro(int dest[MAX_N][MAX_M], int src[MAX_N][MAX_M]) {
    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_M; j++)
            dest[i][j] = src[i][j];
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
