#include <string.h>
#include "tp.h"
#include "backtracking.h"
#include "bruteforce.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <estrategia>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    if (strcmp(argv[2], "backtracking") == 0) {
        backtracking(fp);
    } else if (strcmp(argv[2], "bruteforce") == 0) {
        bruteforce(fp);
    } else {
        fprintf(stderr, "Estrategia invalida: %s\n", argv[2]);
    }

    fclose(fp);
    return 0;
}
