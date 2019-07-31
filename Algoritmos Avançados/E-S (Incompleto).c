/*
***************************************************

	USP - ICMC
	ALG - SCC0210 - 2018
	
	Entrada/Saida 1

	Março - 2018

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int transforma(char* n, int a){

	int m;
	int b = a - 1;
	int aux = 0;

	for(int cont = 0; cont < a; cont++){
		m = aux + (n[cont] - 48) * pow(10, b);
		b--;
		aux = m;
	}

	return m;

}

int main(){

	int n;			//numero de linhas
	char** numeros;	//numeros que vão servir para contagem
	char* aux;
	int* resul;
	int a = 0;

	scanf("%d", &n);
	getchar();

	numeros = (char**)calloc(n + 1, sizeof(char*));
	for(int cont = 0; cont < n + 1; cont++){
		numeros[cont] = (char*)calloc(100, sizeof(char));
	}

	aux = (char*)calloc(10, sizeof(char));

	resul = (int*)calloc(1000, sizeof(int));

	for(int cont = 0; cont < n; cont++){
		fgets(numeros[cont], 100, stdin);
	}

	for(int cont = 0; cont < n; cont++){
		for(int cont1 = 0; cont1 < strlen(numeros[cont]); cont1++){
			int m = 0;
			//printf("entrou\n");
			if(numeros[cont][cont1] != ' ' && numeros[cont][cont1] != '\n'){
				aux[m] = numeros[cont][cont1];
				//printf("-- %c", aux[m]);
				m++;
			}
			else if(numeros[cont][cont1] == '\0' || numeros[cont][cont1] == ' ' || numeros[cont][cont1] == '\n'){
				if(aux[0] != 0){
					resul[a] = transforma(aux, strlen(aux));
					//printf("- %d\n", resul[a]);
					a++;
					for(int cont2 = 0; cont2 < 10; cont2++){
						aux[cont2] = 0;
					}
				}
			}
		}
	}

	int soma = 0;
	int aux1 = 0;

	for(int cont = 0; cont < a; cont++){
		soma = aux1 + resul[cont];
		aux1 = soma;
		//printf(" soma %d\n", soma);
	}

	printf("%d\n", soma);

	return 0;

}