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
