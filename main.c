#include <string.h>
#include <unistd.h>
#include "tp.h"
#include "backtracking.h"
#include "bruteforce.h"

int main(int argc, char *argv[]) {
    char *entrada = NULL;
    char *saida = NULL;
    int estrategia = 0;
    int opcao; 

    // Tratamento das opções com getopt
    while ((opcao = getopt(argc, argv, "i:o:s:")) != -1) {
        switch (opcao) {
            case 'i':
                entrada = optarg;
                break;
            case 'o':
                estrategia = atoi(optarg);
                break;
            case 's':
                saida = optarg;
                break;
            default:
                fprintf(stderr, "Uso: %s -i <entrada.txt> -o <1 para forca bruta|2 para backtracking> -s <saida.txt>\n", argv[0]);
                return 1;
        }
    }

    // Verifica se todos os argumentos necessários foram passados
    if (!entrada || !saida || (estrategia != 1 && estrategia != 2)) {
        fprintf(stderr, "Parâmetros obrigatórios faltando ou inválidos.\n");
        fprintf(stderr, "Uso: %s -i <entrada.txt> -o <1 para forca bruta|2 para backtracking> -s <saida.txt>\n", argv[0]);
        return 1;
    }

    //Abre o arquivo de entrada para leitura e o arquivo de saída para escrita
    FILE *fp = fopen(entrada, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    FILE *out = fopen(saida, "w");
    if (!out) {
        perror("Erro ao criar arquivo de saída");
        fclose(fp);
        return 1;
    }

    // Marca o início da medição de tempo de CPU
    struct rusage uso_inicio, uso_fim;
    getrusage(RUSAGE_SELF, &uso_inicio);

    // Escolhe qual algoritmo será usado com base no argumento
    if (estrategia == 1) {
        bruteforce(fp, out);
    } else if (estrategia == 2) {
        backtracking(fp, out);
    } else {
        fprintf(stderr, "Estrategia invalida: %s\n", argv[2]);
    }

    fclose(fp);
    fclose(out);

    // Marca o fim da medição de tempo de CPU
    getrusage(RUSAGE_SELF, &uso_fim);
    imprimir_tempos(&uso_inicio, &uso_fim); // Imprime tempo de usuário e sistema
    return 0;
}