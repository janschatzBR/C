#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int **  criaMatriz ( int linha, int coluna);

void leituraMatriz(int ** m, int linha, int coluna);

void escritaMatriz( int **m, int linha, int coluna);

	int calculo( int ** a, int ** b, int linha, int coluna, int igual);

