#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"

#define LIMITE 100

int ** matrizC, **aux;

int main() {

	int shmid,status;
	struct shmid_ds shmds;
	int i ;
	int limite, espera;
	pid_t pid, vetor[LIMITE];
	int vet_id[LIMITE];

 int linha = 0, filho = 0 , coluna = 0;
	int **matrizA, **matrizB;
	int linhaA, colunaA, linhaB, colunaB, linhaC, colunaC;
		
	printf("Digite o numero de linhas: ");
	scanf("%d", &linhaA);  
    
	printf("\nDigite o numero de colunas: ");
	scanf("%d", &colunaA);
	
	matrizA = criaMatriz( linhaA, colunaA);		
	leituraMatriz (matrizA, linhaA, colunaA);
	escritaMatriz (matrizA, linhaA, colunaA);

	printf("\nDigite o numero de linhas: ");
	scanf("%d", &linhaB);  
    
	printf("\nDigite o numero de colunas: ");
	scanf("%d", &colunaB);
    
	matrizB = criaMatriz( linhaB, colunaB);
	leituraMatriz (matrizB, linhaB, colunaB);
	escritaMatriz (matrizB,linhaB, colunaB);

	limite = linhaA*colunaB;

	linhaC=linhaA;
	colunaC=colunaB;

	// aloca linhas de C: vetor de ponteiros
	matrizC=(int **)malloc(linhaC*sizeof(int));

	// aloca colunas das linhas de C: na memória compartilhada
	for(i=0;i<linhaC;i++) {
		if((vet_id[i]=shmget(IPC_PRIVATE,colunaC*sizeof(int),0700)) == -1) {
			perror("Erro na alocação da memória compartilhada");
			exit(0);
		}
		matrizC[i] = (int *)shmat(vet_id[i], 0, 0);
	}
	
	// alocação foi bem sucedida

	// matrizC = criaMatriz(linhaA, colunaB);
	// aux = criaMatriz(linhaA,colunaB);

	int l = 0;

	for (filho=0; filho < linhaC; filho++){
		for ( coluna = 0 ; coluna < colunaC ; coluna++ )		
		{printf("\n Criando processo %d", filho);
		if ((vetor[filho] = fork()) < 0){
			printf("Erro na criacao do processo filho\n");
       			fflush(stdout);
		}
		if(vetor[filho] == 0) {
			i = 0;					
	              	for ( ; i < filho; i++)
				pid = waitpid(vetor[i],&status,0);
			
			linha = filho % linhaA ;
			
	
			printf("\nLINHA: %d	COLUNA: %d\n",linha,coluna);

			matrizC[linha][coluna]= calculo(matrizA, matrizB,linha, coluna, colunaA);

			exit(0);
		}
		}
	}			

	status = shmdt((int ** ) matrizC);

	printf("\n liberei %d %d", status, filho);
		
	printf("\n Paiiiiiiii");
	for (espera=0; espera < limite; espera++)
		pid=waitpid(vetor[espera],&status, 0);	
					
		
	escritaMatriz(matrizC,linhaA,colunaB);
		
	printf(" Não esperei");
	printf("\n pai %d",filho );

	// escritaMatriz(aux,linhaA,colunaB);
	status=shmdt((int **) matrizC);
        status=shmctl(shmid,IPC_RMID,&shmds);
	
	free(matrizA);
	free(matrizB);
	free(matrizC);
	
	return (0);



}
