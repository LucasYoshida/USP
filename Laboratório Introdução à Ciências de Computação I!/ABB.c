/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Aula 9 - 1 - Editor de Arvore Binaria de Busca

	Outubro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//*************************TAD ARVORE**************************

typedef struct no {

	int item;
	struct no *esq, *dir;

} t_no;

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

void encontraMaxMin(t_apontador A, t_apontador *R){

	if((*R)->dir != NULL)
		encontraMaxMin(A, &(*R)->dir);
	else{
		A->item = (*R)->item;
		A = (*R);
		(*R) = (*R)->esq;
		free(A);
	}
}

void removeItem(t_arvore *A, int C, int* achou){

	t_apontador p;

	if(*A == NULL){
		return;
	}
	else{
		if(C < (*A)->item)
			removeItem(&(*A)->esq, C, achou);
		else if (C > (*A)->item)
			removeItem(&(*A)->dir, C, achou);
			else
				if((*A)->esq == NULL && (*A)->dir == NULL){
					free(*A);
					*A = NULL;
					*achou = 1;
					return;
				}
				else if((*A)->dir == NULL){
					p = *A;
					(*A) = (*A)->esq;
					free(p);
					p = NULL;
					*achou = 1;
					return;
				}
				else if((*A)->esq == NULL){
					p = *A;
					(*A) = (*A)->dir;
					free(p);
					p = NULL;
					*achou = 1;
					return;
				}
				else{
					int q;
					p = (*A)->dir;
					while(p->esq != NULL){
						p = p->esq;
					}
					q = (*A)->item;
					(*A)->item = p->item;
					p->item = q;
					removeItem(&(*A)->dir, C, achou);
				}
	}

}

void insereItem(t_arvore *A, int C){

	if((*A) == NULL){
		criaRaiz(A, C);
	}
	else{
		if((*A)->item < C){
			insereItem(&(*A)->dir, C);
		}
		else if((*A)->item > C){
			insereItem(&(*A)->esq, C);
		}
		else{
			printf("Chave existente\n");
			return;
		}
	}

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

void posOrdem(t_apontador A){

	if(A != NULL){
		posOrdem(A->esq);
		posOrdem(A->dir);
		printf("%d ", A->item);
	}

}

void emOrdem(t_apontador A){

	if(A != NULL){
		emOrdem(A->esq);
		printf("%d ", A->item);
		emOrdem(A->dir);
	}

}

//*****************TAD FILA*********************

//struct que representa uma implementacao de uma fila
typedef struct {

	int item[1000];		//itens da fila
	int inicio, fim;	//inicio e fim da fila (sendo o inicio sempre 0)

} t_fila;

/*Funcao para colocar os itens na fila
Retorno: 
	void
Parametros:
	t_fila* A = uma fila qualquer
	int item = item a ser colocado na fila
*/
void insereFila (t_fila* A, int item){

	(*A).item[(*A).fim] = item;
	(*A).fim++; 

}

/*Funcao que retira um item da fila (retira sempre o primeiro item da fila)
Retorno:
	void
Parametros:
	t_fila A = uma fila qualquer
*/
int retiraFila (t_fila* A){

	int aux;

	aux = (*A).item[0];

	for(int cont = 0; cont < (*A).fim - 1; cont++){
		(*A).item[cont] = (*A).item[cont + 1];
	}
	//coloca um '\0' no lugar (como se fosse um NULL)
	(*A).item[(*A).fim] = '\0';
	(*A).fim--;

	return aux;

}

/*Funcao que inicializa a fila 
Retorno:
	void
Parametros:
	t_fila* A = uma fila qualquer
*/
void inicializaFila (t_fila* A){

	for(int cont = 0; cont < 1000; cont++){
		(*A).item[cont] = 0;
	}

	(*A).inicio = 0;
	(*A).fim = 0;

}

//****************************************************

void ordemIn(t_apontador A){

	printf("InOrdem: ");
	emOrdem(A);
	printf("\n");

}

void ordemPre(t_apontador A){

	printf("PreOrdem: ");
	preOrdem(A);
	printf("\n");

}

void ordemPos(t_apontador A){

	printf("PosOrdem: ");
	posOrdem(A);
	printf("\n");

}

void largura(t_apontador A){

	t_fila B;
	t_apontador C;
	int aux = 0;		

	printf("Largura: ");

	inicializaFila(&B);

	insereFila(&B, A->item);

	while(B.inicio != B.fim){
		aux = retiraFila(&B);
		printf("%d ", aux);

		C = pesquisa(A, aux);

		if(C->esq != NULL){
			insereFila(&B, C->esq->item);
		}
		if(C->dir != NULL){
			insereFila(&B, C->dir->item);
		}		
	}

	printf("\n");

}

//****************************************************

int main () {

	char entrada;		//guarda a entrada
	int ent;
	t_arvore A;			//arvore
	t_apontador B;
	int achou = 0;

	criaArvore(&A);

	while(entrada != 'X'){
		scanf("%c", &entrada);
		achou = 0;
		if(entrada == 'I'){
			scanf("%d", &ent);
			insereItem(&A, ent);
		}
		if(entrada == 'N'){
			ordemIn(A);
		}
		if(entrada == 'E'){
			ordemPre(A);
		}
		if(entrada == 'O'){
			ordemPos(A);
		}
		if(entrada == 'Y'){
			ordemIn(A);
			ordemPre(A);
			ordemPos(A);
			largura(A);
		}
		if(entrada == 'L'){
			largura(A);
		}
		if(entrada == 'D'){
			scanf("%d", &ent);
			removeItem(&A, ent, &achou);
			if(achou == 0){
				printf("Nao encontrado\n");
			}
			else{
				printf("%d\n", ent);
			}
		}
		if(entrada == 'B'){
			scanf("%d", &ent);
			B = pesquisa(A, ent);
			if(B == NULL){
				printf("Nao encontrado\n");
			}
			else{
				printf("Encontrado\n");
			}
		}
	}

	return 0;

}