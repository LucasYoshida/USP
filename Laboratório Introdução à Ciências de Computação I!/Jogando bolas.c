/*
***************************************************

	USP - ICMC
	LAB ICC2 - 2017
	
	Aula 10 - Jogando Bolas

	Novembro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no{

	struct no* dir;		//aponta para proximo no na direita
	struct no* esq;		//aponta para proximo no na esquerda
	int flag;			//flag configurada para nos nao terminais
	int item;			//numero que representa o no

}t_no;

typedef t_no *t_apontador;

typedef t_apontador t_arvore;

void criaArvore (t_arvore *A){

	*A = NULL;

}

void criaRaiz (t_arvore *A, int item){

	*A = (t_apontador) malloc(sizeof(t_no));
	(*A)->dir = NULL;
	(*A)->esq = NULL;
	(*A)->item = item;

}

void insereDireita(t_arvore A, int item){

	criaRaiz(&A->dir, item);

}

void insereEsquerda(t_arvore A, int item){

	criaRaiz(&A->esq, item);

}

t_apontador pesquisa(t_arvore A, int C){

	if(A != NULL){
		if(A->item == C){		
			return A;
		}
		if(C < A->item)
			return pesquisa(A->esq, C);
		else
			return pesquisa(A->dir, C);
	}

	return NULL;

}

void preOrdem(t_apontador A){

	if(A != NULL){
		printf("%d ", A->item);
		preOrdem(A->esq);
		preOrdem(A->dir);
	}

}

void emOrdem(t_apontador A){

	if(A != NULL){
		emOrdem(A->esq);
		printf("%d ", A->item);
		emOrdem(A->dir);
	}

}

void posOrdem(t_apontador A){

	if(A != NULL){
		posOrdem(A->esq);
		posOrdem(A->dir);
		printf("%d ", A->item);
	}

}

/*Funcao que monta a arvore binaria ate o nivel passado por D
Retorno:
	void
Parametros:
	t_arvore* A = uma arvore qualquer 
	int item = numero do no representante da arvore
	int max = numero maximo que a arvore pode atingir
	int* aux = ajuda com o maximo de nos
*/
void montaArvore(t_arvore* A, int item, int max, int* aux){

	if(item < (*aux)){
		insereEsquerda(*A, item * 2);
		insereDireita(*A, (item * 2) + 1);
		montaArvore(&(*A)->esq, item * 2, max, aux);
		montaArvore(&(*A)->dir, (item * 2) + 1, max, aux);
	}
	else if((*aux) < max){
		(*aux)++;
	}

}

/*Funcao que percorre a arvore binaria conforme o problema
Retorno:
	void
Parametros:
	t_apontador A = para percorrer a arvore
	int* vet = vetor que guarda as folhas da arvore
	int* aux = ajuda com a alocacao no vetor
*/
void percorreArvore(t_apontador A, int* vet, int* aux){

	if(A != NULL){
		percorreArvore(A->esq, vet, aux);
		if(A->esq == NULL && A->dir == NULL){
			vet[*aux] = A->item;
			(*aux)++;
		}
		percorreArvore(A->dir, vet, aux);
	}

}

//**********************MAIN************************

int main (){

	int D;		//profundidade da arvore
	int I;		//numero de bolas a ser joagada
	t_arvore A;	//arvore para as bolas
	int numero;	//numero que representa o no	

	//entrada
	scanf("%d %d", &D, &I);

	criaArvore(&A);

	numero = 1;

	criaRaiz(&A, numero);

	int max;

	max = pow(2, D) - 1;

	int aux;

	aux = pow(2, (D-1));

	montaArvore(&A, numero, max, &aux);

	aux = 0;
	max = pow(2, (D-1)) + 1;
	int vet[max];

	percorreArvore(A, vet, &aux);

	aux = max - 1;
	int aux1 = aux/2;
	int vet1[max];	
	int aux3 = 0;
	int flag = 0;
	int aux4 = aux1;

	for(int cont = 0; cont < aux1; cont++){
		if(flag == 0){
			vet1[cont] = vet[aux3];
			aux3 += 2;
			flag = 1;
		}
		else{
			vet1[cont] = vet[aux4];
			aux4 += 2;
			flag = 0;	
		}
	}

	aux3 = 1;
	aux4 = aux1 + 1;

	for(int cont = aux1; cont < aux; cont++){
		if(flag == 0){
			vet1[cont] = vet[aux3];
			aux3 += 2;
			flag = 1;
		}
		else{
			vet1[cont] = vet[aux4];
			aux4 += 2;
			flag = 0;	
		}
	}

	if(D < 3)
		printf("%d\n", vet[I-1]);
	else
		printf("%d\n", vet1[I-1]);

	return 0;

}