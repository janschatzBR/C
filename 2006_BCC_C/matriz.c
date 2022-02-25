#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "matriz.h"


int **  criaMatriz ( int linha, int coluna){

   int ** m;	

    m =  calloc (linha, sizeof(int));	   

    int  i = 0;
    for (i ; i < linha; ++ i)
	 m[i] = calloc (coluna, sizeof(int));
       
    return m;
}

void leituraMatriz(int ** m, int linha, int coluna){
     
	int i = 0, j, valor;
 	for (i ; i < linha; ++i){
      	   j = 0;	  
	   for (j ; j < coluna; ++j){
             printf("\nDigite o elemento M[%d][%d]: ", i, j);
	     scanf("%d",& valor);
	     m[i][j] = valor;

         }
      }
}

void escritaMatriz( int **m, int linha, int coluna){

     int i = 0,j;
     for (i ; i < linha; ++i){
         j = 0;	
	 for (j ; j < coluna; ++j)
             printf("M[%d][%d]: %d ", i, j, m[i][j]);
     }
                    
}

int calculo(int ** a, int ** b, int linha, int coluna,int igual){
	int soma=0, i = 0;
	for ( i ; i < igual; ++i){
		
		soma += a[linha][i] * b[i][coluna];
		printf("Calculando %d * %d = %d", a[linha][i], b[i][coluna], soma);
	}

	
	printf("\nresultado: %d",soma);
	return soma;
	
}     


