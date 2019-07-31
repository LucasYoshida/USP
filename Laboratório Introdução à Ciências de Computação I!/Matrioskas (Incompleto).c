/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Aula 6 - Matrioskas

	Setembro - 2017

	Lucas Noriyuki Yoshida - 10262586

***************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Funcao que encontra se existe ou nao matrioskas
Retorno:
	void
Parametros:
	int *vetor == //vetor que guarda as possiveis matrioskas
	int aux1 == guarda o fim da contagem
	int* N == guarda a quantidade de matrioskas
	int ajuda == ajuda com o inicio da contagem
	int* erro == indica se tem um erro
*/
void encontra (int* vetor, int aux1, int* N, int ajuda, int* erro){

	int aux2 = 0;
	//printf("aux1 -> %d ajuda -> %d\n", aux1, ajuda);

	//se tem uma parte sozinha ou se tem partes iguais (bonecas de mesmo tamanho)
	if(aux1 == ajuda || vetor[ajuda] == vetor[ajuda-1]){
		aux2 = *erro;
	  	*erro = aux2 + 1;
	}

	for(int cont = ajuda + 1; cont <= aux1; cont++){
	  	//printf("cont -> %d\n", cont);
	  	if(cont == ajuda+1 && vetor[cont] > vetor[ajuda]){
	  		aux2 = *erro;
	  		*erro = aux2 + 1;
	  	} 
		if(vetor[ajuda] == vetor[cont]){
		 	//printf("entorursahjfkiuew\n");
			if(cont != aux1){
			  	//printf("-2\n");
			  	if(cont == ajuda + 1){
					aux2 = *N;
					aux2++;
					*N = aux2;
					//printf("N -->%d\n", *N);
				}
			  	else{
			  		encontra(vetor, cont-1, N, ajuda+1, erro);
				}
				return encontra(vetor, aux1, N, cont+1, erro);
			}
			else{
				if(cont == ajuda + 1){
					aux2 = *N;
					aux2++;
					*N = aux2;
					//printf("N -->%d\n", *N);
				}
				else{
				  	//printf("1\n");
					return encontra(vetor, cont-1, N, ajuda+1, erro);
				}
			}
		}
	}

}

/*Funcao que separa a linha em pequenas strings
Retorno:
	int N == '0' 				//erro: '=( Tente novamente'
	int N == 'n'				//numero de matrioskas
Parametros:
	char** matrioska;		//linhas que repressentam as possiveis matrioskas
*/
int separa (char* matrioska){

	char** matriz;		//matriz que serve para ajudar na comparacao dos numeros
	int erro = 0;		//indica se tem erro
	int* vetor;			//vetor que guarda as possiveis matrioskas

	matriz = (char**)calloc(100, sizeof(char*));
	for(int cont = 0; cont < 100; cont++){
		matriz[cont] = (char*)calloc(5, sizeof(char));
	}

	vetor = (int*)calloc(200, sizeof(int));

	int aux = 0;
	int aux1 = 0;
	int aux4 = 0;

	//separando a linha em pequenas strings e depois num vetor int
	for(int cont = 0; cont < strlen(matrioska); cont++){
		if(matrioska[cont] == ' '){
			int aux2 = 0;
			for(int cont1 = aux; cont1 < cont; cont1++){
				if(matrioska[cont1] == '-'){
					cont1++;
				}
				matriz[aux1][aux2] = matrioska[cont1];
				//printf("%c", matriz[aux1][aux2]);
				aux2++;
			}
			aux2--;
			int aux3 = 0;
			int n, m, o = 0;
			for(int cont1 = aux2; cont1 >= 0; cont1--){
				n = (int)matriz[aux1][aux3];
				m = o + ((n - 48)*pow(10, cont1));
				o = m;
				aux3++;
			}
			vetor[aux4] = o;
			//printf("%d\n", vetor[aux4]);
			aux4++;
			aux1++;
			aux = cont + 1;
		}
	}

	aux1--;

	int N = 0;
	int aux2 = 0;

	encontra(vetor, aux1, &N, aux2, &erro);

	//free
	for(int cont = 0; cont < 100; cont++){
		free(matriz[cont]);
	}
	free(matriz);
	free(vetor);

	if(erro > 0){
		N = 0;
	}

	return N;

}

//*****************************************************************************

int main () {

	int L;					//numero de linhas a serem avaliadas
	char** matrioska;		//linhas que repressentam as possiveis matrioskas
	int N = 0;				//guarda se encontrou ou nao as matrioskas

	scanf("%d", &L);
	getchar();
	getchar();

	//alocacao das possiveis matrioskas
	matrioska = (char**)calloc(L, sizeof(char*));
	for(int cont = 0; cont < L; cont++){
		matrioska[cont] = calloc(2000, sizeof(char));
	}

	for(int cont = 0; cont < L; cont++){
		//entrada das frases
		fgets(matrioska[cont], 2000, stdin);
		//printf("%s\n", matrioska[cont]);
		//retira a quebra de linha e o '0'
		if(cont < L-1){
			matrioska[cont][strlen(matrioska[cont])-3] = '\0';
		}
		else{
			matrioska[cont][strlen(matrioska[cont])-2] = '\0';	
		}
	}

	for(int cont = 0; cont < L; cont++){
		N = separa(matrioska[cont]);
		if(N == 0){
			printf("=( Tente novamente\n");
		}
		else{
			printf("=) Matrioska %d\n", N);
		}
	}

	//frees
	for(int cont = 0; cont < L; cont++){
		free(matrioska[cont]);
	}
	free(matrioska);

	return 0;

}