#include "tp.h"

int capturar_bf(int **tab, int x, int y, int capturas_atuais)
{
    int max_capturas = capturas_atuais;
    int houve_captura = 0;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nx2 = nx + dx[i];
        int ny2 = ny + dy[i];

        if (dentro_limites(nx2, ny2) && tab[nx][ny] == 2 && tab[nx2][ny2] == 0)
        {
            houve_captura = 1;

            // Cria uma nova cópia do tabuleiro
            int **copia = alocar_tabuleiro(N, M);
            copiar_tabuleiro(copia, tab, N, M);

            // Executa a jogada na cópia
            copia[x][y] = 0;
            copia[nx][ny] = 0;
            copia[nx2][ny2] = 1;

            int capturas = capturar_bf(copia, nx2, ny2, capturas_atuais + 1);
            if (capturas > max_capturas)
                max_capturas = capturas;

            liberar_tabuleiro(copia, N);
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
                    int c = capturar_bf(copia, i, j, 0);
                    if (c > max_capturas)
                        max_capturas = c;
                    liberar_tabuleiro(copia, N);
                }

        fprintf(out, "%d\n", max_capturas);
        liberar_tabuleiro(tabuleiro, N);
    }

    return 0;
}
