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
extern int tabuleiro[MAX_N][MAX_M];
extern int dx[4];
extern int dy[4];

int dentro_limites(int x, int y);
void copiar_tabuleiro(int dest[MAX_N][MAX_M], int src[MAX_N][MAX_M]);

#endif // TP_H
