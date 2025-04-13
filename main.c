#include <stdio.h>

#define MAX_N 20
#define MAX_M 20

int N, M;
int tabuleiro[MAX_N][MAX_M];

// Direções possíveis para capturas (diagonais)
int dx[] = {-1, -1, 1, 1};
int dy[] = {-1, 1, -1, 1};

// Função para verificar se a posição (x, y) está dentro dos limites do tabuleiro
int dentro_limites(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < M);
}

// Função recursiva para calcular o número máximo de capturas a partir de uma posição (x, y)
int capturar_maximo(int x, int y) {
    int max_capturas = 0;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];  // Próxima casa na diagonal
        int ny = y + dy[i];

        int nx2 = nx + dx[i]; // Casa seguinte (onde a peça pode pular)
        int ny2 = ny + dy[i];

        // Verifica se pode capturar: casa com peça do oponente e casa seguinte vazia
        if (dentro_limites(nx2, ny2) && tabuleiro[nx][ny] == 2 && tabuleiro[nx2][ny2] == 0) {
            // Captura temporária
            tabuleiro[nx][ny] = 0; // Remove peça do oponente
            tabuleiro[x][y] = 0;   // Move peça do jogador
            tabuleiro[nx2][ny2] = 1;

            // Busca o máximo de capturas possíveis após essa jogada
            int capturas = 1 + capturar_maximo(nx2, ny2);
            if (capturas > max_capturas) {
                max_capturas = capturas;
            }

            // Desfaz a jogada (backtracking)
            tabuleiro[nx][ny] = 2;
            tabuleiro[x][y] = 1;
            tabuleiro[nx2][ny2] = 0;
        }
    }

    return max_capturas;
}

int main() {
        scanf("%d %d", &N, &M);
        if (N == 0 && M == 0) return 0; // Fim da entrada

        // Leitura do tabuleiro (usando vetor linear e mapeando para matriz)
        int total_casas = (N * M) / 2;
        for (int i = 0; i < total_casas; i++) {
            int valor;
            scanf("%d", &valor);
            
            // Converter índice do vetor para posição (linha, coluna)
            int linha = (2 * i) / M;
            int coluna = (2 * i) % M;
            
            // Garantir que a peça está em uma casa branca
            if ((linha + coluna) % 2 == 1) coluna++;

            tabuleiro[linha][coluna] = valor;
        }

        // Buscar a melhor jogada para todas as peças do jogador
        int max_capturas = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (tabuleiro[i][j] == 1) {
                    int capturas = capturar_maximo(i, j);
                    if (capturas > max_capturas) {
                        max_capturas = capturas;
                    }
                }
            }
        }

        printf("%d\n", max_capturas);
}
