#include "backtracking.h"

int capturar_maximo(int x, int y) {
    int max_capturas = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nx2 = nx + dx[i];
        int ny2 = ny + dy[i];

        if (dentro_limites(nx2, ny2) && tabuleiro[nx][ny] == 2 && tabuleiro[nx2][ny2] == 0) {
            tabuleiro[x][y] = 0;
            tabuleiro[nx][ny] = 0;
            tabuleiro[nx2][ny2] = 1;

            int capturas = 1 + capturar_maximo(nx2, ny2);
            if (capturas > max_capturas)
                max_capturas = capturas;

            tabuleiro[x][y] = 1;
            tabuleiro[nx][ny] = 2;
            tabuleiro[nx2][ny2] = 0;
        }
    }
    return max_capturas;
}

int backtracking(FILE *fp) {
    while (fscanf(fp, "%d %d", &N, &M) == 2 && (N != 0 || M != 0)) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                tabuleiro[i][j] = ((i + j) % 2 == 0) ? ({ int v; fscanf(fp, "%d", &v); v; }) : 0;

        int max_capturas = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (tabuleiro[i][j] == 1) {
                    int c = capturar_maximo(i, j);
                    if (c > max_capturas) max_capturas = c;
                }

        printf("%d\n", max_capturas);
    }
    return 0;
}
