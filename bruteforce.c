#include "bruteforce.h"

int capturar_maximobf(int **tab, int x, int y)
{
    int max_capturas = 0;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nx2 = nx + dx[i];
        int ny2 = ny + dy[i];

        if (dentro_limites(nx2, ny2) && tab[nx][ny] == 2 && tab[nx2][ny2] == 0)
        {
            // Realiza jogada
            tab[x][y] = 0;
            tab[nx][ny] = 0;
            tab[nx2][ny2] = 1;

            int capturas = 1 + capturar_maximobf(tab, nx2, ny2);
            if (capturas > max_capturas)
                max_capturas = capturas;

            tab[x][y] = 1;
            tab[nx][ny] = 2;
            tab[nx2][ny2] = 0;
        }
    }

    return max_capturas;
}


int bruteforce(FILE *fp, FILE *out)
{
    while (fscanf(fp, "%d %d", &N, &M) == 2 && (N != 0 || M != 0))
    {
        tabuleiro = alocar_tabuleiro(N, M);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                tabuleiro[i][j] = ((i + j) % 2 == 0) ? ({ int v; fscanf(fp, "%d", &v); v; }) : 0;

        int max_capturas = 0;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (tabuleiro[i][j] == 1)
                {
                    int **copia = alocar_tabuleiro(N, M);
                    copiar_tabuleiro(copia, tabuleiro, N, M);
                    int c = capturar_maximobf(copia, i, j);
                    if (c > max_capturas)
                        max_capturas = c;
                    liberar_tabuleiro(copia, N);
                }

        fprintf(out, "%d\n", max_capturas);
        liberar_tabuleiro(tabuleiro, N);
    }

    return 0;
}
