#include "tp.h"

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
    
    backtracking(fp, max_capturas);

    fclose(fp);
    return 0;
}