#include "backtracking.h"

int melhor_solucao = 0;

int contar_inimigos(int **tab) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (tab[i][j] == 2)
                count++;
    return count;
}

void capturar_backtracking(int **tab, int x, int y, int capturas_atuais)
{
    int captura_feita = 0;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nx2 = nx + dx[i];
        int ny2 = ny + dy[i];

        if (dentro_limites(nx2, ny2) && tab[nx][ny] == 2 && tab[nx2][ny2] == 0)
        {
            captura_feita = 1;

            tab[x][y] = 0;
            tab[nx][ny] = 0;
            tab[nx2][ny2] = 1;

            int restantes = contar_inimigos(tab);
            if (capturas_atuais + 1 + restantes > melhor_solucao) {
                capturar_backtracking(tab, nx2, ny2, capturas_atuais + 1);
            }

            tab[x][y] = 1;
            tab[nx][ny] = 2;
            tab[nx2][ny2] = 0;
        }
    }

    if (!captura_feita && capturas_atuais > melhor_solucao)
    {
        melhor_solucao = capturas_atuais;
    }
}

int backtracking(FILE *fp, FILE *out)
{
    while (fscanf(fp, "%d %d", &N, &M) == 2 && (N != 0 || M != 0))
    {
        if (N<3 || N > 20 || M < 3 || M >20 || N * M > 200){
            fprintf(out, "Erro: valores de N ou M inválidos (N=%d, M=%d)\n", N, M);
            return 1;
        }
        
        melhor_solucao = 0;
        tabuleiro = alocar_tabuleiro(N, M);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                tabuleiro[i][j] = ((i + j) % 2 == 0) ? ({ int v; fscanf(fp, "%d", &v); v; }) : 0;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (tabuleiro[i][j] == 1)
                {
                    int **copia = alocar_tabuleiro(N, M);
                    copiar_tabuleiro(copia, tabuleiro, N, M);
                    capturar_backtracking(copia, i, j, 0);
                    liberar_tabuleiro(copia, N);
                }

        fprintf(out, "%d\n", melhor_solucao);
        liberar_tabuleiro(tabuleiro, N);
    }

    return 0;
}
