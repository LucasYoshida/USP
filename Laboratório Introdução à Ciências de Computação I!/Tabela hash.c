/*
***************************************************

	USP - ICMC
	LAB ICC2 - 2017
	
	Aula 14- Tabela Hash

	Dezembro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/
#include <stdio.h>
#include <stdlib.h>

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

void inOrden(t_apontador A){

	if(A != NULL){
		inOrden(A->esq);
		printf("%d ", A->item);
		inOrden(A->dir);
	}

}


//****************************************************

void insere(t_arvore* table, int x){

	if((*table) == NULL)
		criaRaiz(&*(table), x);
	else
		insereItem(&*(table), x);

}

void emOrdem(t_apontador A, int* vet, int* quant){

	int aux;

	if(A != NULL){
		emOrdem(A->esq, vet, quant);
		vet[*quant] = A->item;
		aux = *quant;
		*quant = aux + 1;
		emOrdem(A->dir, vet, quant);
	}

}

void destroi(t_arvore* A){

	if(*A != NULL){
		destroi(&(*A)->esq);
		destroi(&(*A)->dir);
		free(*A);
	}

}

//****************************************************

int main (){

	char op;			//guarda a operacao
	int num;			//guarda o numero a ser alocado/buscado/removido
	t_arvore* table;	//hash table
	int indice;			//inidce para colocar na hash table
	t_arvore aux;		//auxiliar para ajudar na busca e remocao
	int* vet;			//guarda o vetor para colisao
	int quant;			//quantidade de colisoes;	
	int maior = 0;		//guarda o maior indice da hash


	table = (t_arvore*)calloc(101, sizeof(t_arvore));

	vet = (int*)calloc(101, sizeof(int));

	for(int cont = 0; cont < 100; cont++){
		criaArvore(&table[cont]);
	}

	while(scanf("%c", &op) != EOF){

		//insercao
		if(op == 'i'){
			getchar();
			scanf("%d", &num);
			indice = num % 100;
			if(indice > maior)
				maior = indice;
			insere(&table[indice], num);
		}
		//busca
		else if(op == 'b'){
			getchar();
			scanf("%d", &num);
			indice = num % 100;
			aux = pesquisa(table[indice], num);
			if(aux == NULL)
				printf("nao encontrado\n");
			else
				printf("encontrado\n");
		}
		//remocao
		else if(op == 'r'){
			getchar();
			scanf("%d", &num);
			indice = num % 100;
			pesquisa(table[indice], num);
			if(aux != NULL){
				int achou;
				removeItem(&table[indice], num, &achou);
			}
		}
		//imprimi
		else if(op == 'p'){
			for(int cont = 0; cont < 100; cont++){
				int entrou = 0;
				if(table[cont] != NULL){
					if(table[cont]->dir != NULL || table[cont]->esq != NULL){
						printf("(");
						quant = 0;
						emOrdem(table[cont], vet, &quant);
						for(int cont1 = 0; cont1 < quant; cont1++){
							if(cont1 != quant -1)
								printf("%d, ", vet[cont1]);
							else
								printf("%d)", vet[cont1]);
						}
						entrou = 1;
						if(cont != maior)
							printf(", ");
						else
							printf("\n");
					}
					if(cont != maior && entrou == 0)
						printf("%d, ", table[cont]->item);
					else if(cont == maior && entrou == 0)
						printf("%d\n", table[cont]->item);
				}
			}
		}

	}

	for(int cont = 0; cont < 100; cont++){
		if(table[cont] != NULL);
			destroi(&table[cont]);
	}
	free(table);
	free(vet);

}