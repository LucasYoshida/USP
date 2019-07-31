/*
***************************************************

	USP - ICMC
	LAB ICC II - 2017
	
	Aula 4 - Números Imensos

	Setembro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funcao que transforma o numero em positivo
void positivo (char* primeiro, char* segundo, int negativo){

	char letra;

	if (negativo == 1){
		for(int i = 1; i > strlen(primeiro); i++){
		letra = primeiro[i];
		primeiro[i-1] = letra;
		}
		for(int i = 1; i > strlen(segundo); i++){
			letra = segundo[i];
			segundo[i-1] = letra;
		}
	}

	if(negativo == 2){
		for(int i = 1; i > strlen(primeiro); i++){
		letra = primeiro[i];
		primeiro[i-1] = letra;
		}
	}

}

//Funcao que printa o resultado da soma
void printar_soma (int cont2, int* resul){

	for(int cont = cont2; cont <= 100; cont++){
		printf("%d",resul[cont]);
	}
	printf("\n");

}

//Funcao que faz a soma
void soma (char* mod, char* mod1, int* resul, int max, int negativo){
	
	int carry = 0;		//carry caso haja
	int aux = 0;		//auxiliador para as contas
	int cont2 = 100;
	int a, b;		//auxiliam no calculo da soma
	for(int cont = 1; cont <= max; cont++){
		a = mod1[strlen(mod1) - cont] - 48;
		b = mod[strlen(mod) - cont] - 48;
		resul[cont2] = a + b + carry;
		if(resul[cont2] >= 10){
			carry = resul[cont2] / 10;
			aux = resul[cont2] % 10;
			resul[cont2] = aux;
		}
		else{
			carry = 0;
		}
		cont2--; 
	}
	resul[cont2] = carry;
	
	if(carry != 1){
		cont2++;
	}

	if(negativo == 1){
		printf("-");
		cont2++;
	}

	printar_soma(cont2, resul);

}

//Funcao que printa o resultado da subtracao
void printar_sub (int cont2, int* resul){

	for(int cont = 0; cont < cont2; cont++){
		printf("%d",resul[cont]);
	}
	printf("\n");

}
	
//Funcao que faz a subtracao
void subtracao(char* mod, char* mod1, int* resul, int max, int negativo){
	
	int prim[100];	//MAIOR NUMERO
	int seg[100];	//MENOR NUMERO
	int aux;		//auxilia com a subtracao

	for(int cont = 0; cont < max; cont++){
		prim[cont] = mod1[cont] - 48;
		seg[cont] = mod[cont] - 48;
	}
	
	aux = prim[0];
	prim[0] = aux - 1;
		
	for(int cont = 1; cont < max; cont++){
		aux = prim[cont];
		prim[cont] = aux + 10;
	}

	for(int cont = max - 1; cont >= 1; cont--){
		resul[cont] = prim[cont] - seg[cont];
		if(resul[cont] >= 10){
			aux = resul[cont];
			resul[cont] = aux % 10;
		}
	}

	resul[0] = ((prim[1] - seg[1])/10) + (prim[0] - seg[0]);

	printar_sub(max, resul);

}

int main () {

	char operacao[14];	//vetor que guarda a operacao desejada
	char primeiro[100];	//vetor que guarda o primeirp numero
	char segundo[100];	//vetor que guarda o segundo numero
	int resul[100];		//vetor que guarda o resultado para a saida
	int max, min;		//guarda o maior e menor numeros
	int dif;			//diferenca entre os vetores de numeros
	int negativo = 0;	//mostra se era negativo ou nao

	//entrada da operacao
	fgets(operacao, 14, stdin);
	//retira a quebra de linha
	operacao[strlen(operacao)-1] = '\0';

	//entrada do primeiro nuemro
	fgets(primeiro, 100, stdin);
	//retira a quebra de linha
	primeiro[strlen(primeiro)-1] = '\0';
	
	//entrada do segundo numero
	fgets(segundo, 100, stdin);
	segundo[strlen(segundo)-1] = '\0';

	//printf("%s\n", primeiro);
	//printf("%s\n", segundo);
	
	char mod[100] = {'0'};  //vetor que guarda quando um numero for modificado
	char mod1[100] = {'0'};  //vetor que guarda quando um numero que nao foi modificado

	if(primeiro[0] == '-' && segundo[0] == '-'){
		negativo = 1;
		positivo(primeiro, segundo, negativo);
	}

	if(primeiro[0] == '-'){
		negativo = 2;
		positivo(primeiro, segundo, negativo);
	}

	if(strlen(primeiro) <= strlen(segundo)){
		max = strlen(segundo);
		min = strlen(primeiro);
		dif = strlen(segundo) - strlen(primeiro);
		for(int i = 0; i < min; i++){
		  mod[i + dif] = primeiro[i];
		}
		for(int j = dif - 1; j >= 0; j--){
			  mod[j] = '0';
		}
		for(int i = 0; i < strlen(segundo); i++){
			mod1[i] = segundo[i];
		}
	}
	else {
		max = strlen(primeiro);
		min = strlen(segundo);
		dif = strlen(primeiro) - strlen(segundo);
		for(int i = 0; i < min; i++){
		  mod[i + dif] = segundo[i];
		}
		for(int j = dif - 1; j >= 0; j--){
			  mod[j] = '0';
		}
		for(int i = 0; i < strlen(primeiro); i++){
			mod1[i] = primeiro[i];
		}
	}

	//verificacao de qual eh a operacao
	//SOMA
	if(operacao[2] == 'M'){
		soma(mod, mod1, resul, max, negativo);
	}

  	//SUBTRACAO
	if(operacao[2] == 'B'){
		if(negativo == 2){
			negativo = 1;
			soma(mod, mod1, resul, max, negativo);
		}
		subtracao(mod, mod1, resul, max, negativo);
	}

	//MULTIPLICACAO
	if(operacao[2] == 'L'){
		printf("3");
	}

 	//DIVISAO
	if(operacao[2] == 'V'){
		printf("4");
	}

	return 0;

}