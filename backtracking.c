#include "backtracking.h"

// Variável global que guarda a melhor sequência de capturas encontrada
int melhor_solucao = 0;

// Conta quantas peças inimigas (valor 2) ainda existem no tabuleiro
int contar_inimigos(int **tab) {
    int cont = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (tab[i][j] == 2)
                cont++;
    return cont;
}

// Função recursiva que tenta capturar o maior número possível de peças
void capturar_backtracking(int **tab, int x, int y, int capturas_atuais)
{
    int captura_feita = 0; // flag para verificar se ao menos uma captura foi feita

    // Tenta capturar em todas as 4 direções diagonais
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];     // posição da peça inimiga (diagonal)
        int ny = y + dy[i];
        int nx2 = nx + dx[i];   // posição após a peça inimiga (destino do salto)
        int ny2 = ny + dy[i];

        // Verifica se a jogada é válida: tem inimigo e casa atrás está vazia
        if (dentro_limites(nx2, ny2) && tab[nx][ny] == 2 && tab[nx2][ny2] == 0)
        {
            captura_feita = 1;

            // Realiza a captura no tabuleiro atual
            tab[x][y] = 0;
            tab[nx][ny] = 0;
            tab[nx2][ny2] = 1;

            // Aplica poda: só continua se ainda for possível bater a melhor solução
            int restantes = contar_inimigos(tab);
            if (capturas_atuais + 1 + restantes > melhor_solucao) {
                capturar_backtracking(tab, nx2, ny2, capturas_atuais + 1);
            }

            // Backtrack: desfaz a jogada e restaura o tabuleiro
            tab[x][y] = 1;
            tab[nx][ny] = 2;
            tab[nx2][ny2] = 0;
        }
    }

    // Se nenhuma nova captura pôde ser feita, atualiza a melhor solução se for o caso
    if (!captura_feita && capturas_atuais > melhor_solucao)
    {
        melhor_solucao = capturas_atuais;
    }
}

// Lê os casos do arquivo, executa o algoritmo e imprime o resultado
int backtracking(FILE *fp, FILE *out)
{
    // Processa enquanto houver casos de teste (linha com N M diferente de 0 0)
    while (fscanf(fp, "%d %d", &N, &M) == 2 && (N != 0 || M != 0))
    {
        // Verifica se N e M estão dentro dos limites especificados
        if (N < 3 || N > 20 || M < 3 || M > 20 || N * M > 200) {
            // Imprime erro, consome os valores restantes e continua para o próximo caso
            fprintf(out, "Erro: valores de N ou M inválidos (N=%d, M=%d)\n", N, M);
            int quant = (N * M) / 2;
            for (int i = 0; i < quant; i++) {
                int lixo;
                fscanf(fp, "%d", &lixo); // descarta entrada inválida
            }
            continue;
        }

        melhor_solucao = 0;

        // Aloca o tabuleiro dinamicamente com base nos valores de N e M
        tabuleiro = alocar_tabuleiro(N, M);

        // Lê os valores do tabuleiro (somente casas pretas)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                tabuleiro[i][j] = ((i + j) % 2 == 0) ? ({ int v; fscanf(fp, "%d", &v); v; }) : 0;

        // Para cada peça do jogador, inicia a recursão
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (tabuleiro[i][j] == 1)
                {
                    // Cria uma cópia do tabuleiro para não afetar os outros caminhos
                    int **copia = alocar_tabuleiro(N, M);
                    copiar_tabuleiro(copia, tabuleiro, N, M);
                    capturar_backtracking(copia, i, j, 0);
                    liberar_tabuleiro(copia, N);
                }

        // Escreve a melhor solução encontrada no arquivo de saída
        fprintf(out, "%d\n", melhor_solucao);

        // Libera o tabuleiro principal
        liberar_tabuleiro(tabuleiro, N);
    }

    return 0;
}
