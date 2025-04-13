#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_M 20

int N, M;
int tabuleiro[MAX_N][MAX_M];

int dx[] = {-1, -1, 1, 1};
int dy[] = {-1, 1, -1, 1};

int dentro_limites(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

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
            if (capturas > max_capturas) max_capturas = capturas;

            tabuleiro[x][y] = 1;
            tabuleiro[nx][ny] = 2;
            tabuleiro[nx2][ny2] = 0;
        }
    }

    return max_capturas;
}

int main(int argc, char *argv[]) {
    
    int max_capturas = 0;
    
    if (argc != 2) {
        printf("Uso correto: %s arquivo.txt\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    
    while (1) {
        if (fscanf(fp, "%d %d", &N, &M) != 2) break;
        if (N == 0 && M == 0) break;

        // Zerar o tabuleiro
        for (int i = 0; i < MAX_N; i++)
            for (int j = 0; j < MAX_M; j++)
                tabuleiro[i][j] = 0;

        // Preencher casas brancas
        int valor, count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i + j) % 2 == 0) { // Casa branca
                    if (fscanf(fp, "%d", &valor) != 1) {
                        fprintf(stderr, "Erro ao ler valor do tabuleiro.\n");
                        return 1;
                    }
                    tabuleiro[i][j] = valor;
                    count++;
                }
            }
        }

        // Processar capturas
        max_capturas = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (tabuleiro[i][j] == 1) {
                    int capturas = capturar_maximo(i, j);
                    if (capturas > max_capturas)
                        max_capturas = capturas;
                }
            }
        }

        printf("%d\n", max_capturas);
    }

    fclose(fp);
    return 0;
}
