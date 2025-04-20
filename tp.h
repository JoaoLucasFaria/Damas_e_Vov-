// tp.h
#ifndef TP_H
#define TP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_N 20
#define MAX_M 20

extern int N, M;
extern int **tabuleiro;
extern int dx[4];
extern int dy[4];

int dentro_limites(int x, int y);
void copiar_tabuleiro(int **dest, int **src, int linhas, int colunas);
int **alocar_tabuleiro(int linhas, int colunas);
void liberar_tabuleiro(int **tab, int linhas);
void imprimir_tempos(struct rusage *inicio, struct rusage *fim);

#endif // TP
