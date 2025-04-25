#include "tp.h"

// Função recursiva que calcula a quantidade máxima de capturas a partir da posição (x, y)
int capturar_bf(int **tab, int x, int y, int capturas_atuais)
{
    int max_capturas = capturas_atuais;
    int houve_captura = 0; // flag para verificar se alguma jogada foi possível

    // Tenta capturar em todas as 4 direções diagonais
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];     // posição da peça inimiga (diagonal adjacente)
        int ny = y + dy[i];
        int nx2 = nx + dx[i];   // posição após a peça inimiga (pós-captura)
        int ny2 = ny + dy[i];

        // Verifica se é uma jogada válida: inimigo adjacente e casa seguinte vazia
        if (dentro_limites(nx2, ny2) && tab[nx][ny] == 2 && tab[nx2][ny2] == 0)
        {
            houve_captura = 1;

            // Cria uma nova cópia do tabuleiro atual (força bruta pura)
            int **copia = alocar_tabuleiro(N, M);
            copiar_tabuleiro(copia, tab, N, M);

            // Realiza a jogada na cópia
            copia[x][y] = 0;
            copia[nx][ny] = 0;
            copia[nx2][ny2] = 1;

            // Continua recursivamente a partir da nova posição
            int capturas = capturar_bf(copia, nx2, ny2, capturas_atuais + 1);
            if (capturas > max_capturas)
                max_capturas = capturas;

            // Libera a cópia, já que esse caminho foi totalmente explorado
            liberar_tabuleiro(copia, N);
        }
    }

    // Retorna o maior número de capturas possível a partir dessa peça
    return max_capturas;
}

// Lê o arquivo de entrada e processa todos os casos de teste
int bruteforce(FILE *fp, FILE *out)
{
    // Processa enquanto houver casos de teste (linha com N M diferente de 0 0)
    while (fscanf(fp, "%d %d", &N, &M) == 2 && (N != 0 || M != 0))
    {
        // Verifica se os valores de N e M estão dentro dos limites definidos no enunciado
        if (N < 3 || N > 20 || M < 3 || M > 20 || N * M > 200) {
            fprintf(out, "Erro: valores de N ou M inválidos (N=%d, M=%d)\n", N, M);

            // Descarta os valores que seriam lidos para este tabuleiro inválido
            int quant = (N * M) / 2;
            for (int i = 0; i < quant; i++) {
                int lixo;
                fscanf(fp, "%d", &lixo);
            }
            continue;
        }

        // Aloca dinamicamente o tabuleiro principal
        tabuleiro = alocar_tabuleiro(N, M);

        // Lê os valores das casas pretas do tabuleiro (somente onde (i + j) % 2 == 0)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                tabuleiro[i][j] = ((i + j) % 2 == 0) ? ({ int v; fscanf(fp, "%d", &v); v; }) : 0;

        int max_capturas = 0;

        // Para cada peça do jogador, calcula a melhor sequência de capturas
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (tabuleiro[i][j] == 1)
                {
                    // Cria uma cópia do tabuleiro para simular essa jogada separadamente
                    int **copia = alocar_tabuleiro(N, M);
                    copiar_tabuleiro(copia, tabuleiro, N, M);

                    int c = capturar_bf(copia, i, j, 0);
                    if (c > max_capturas)
                        max_capturas = c;

                    liberar_tabuleiro(copia, N);
                }

        // Escreve o resultado deste caso de teste no arquivo de saída
        fprintf(out, "%d\n", max_capturas);

        // Libera o tabuleiro principal ao final do caso
        liberar_tabuleiro(tabuleiro, N);
    }

    return 0;
}
