/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Aula 11.1 - Arvore AVL

	Outubro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

//*************************TAD ARVORE**************************

typedef struct no {

	int item;
	struct no *esq, *dir;
	int fb;

} t_no;

typedef t_no *t_apontador;

typedef t_apontador t_arvore;

void criaArvore (t_arvore *A){

	*A = NULL;

}

t_apontador rot_dir(t_apontador *A){

	t_apontador aux;
	aux = (*A)->esq;
	if(aux != NULL){
		(*A)->esq = aux->dir;
		aux->dir = (*A);
	}
	return aux;

}

t_apontador rot_esq(t_apontador *A){

	t_apontador aux;
	aux = (*A)->dir;
	if(aux != NULL){
		(*A)->dir = aux->esq;
		aux->esq = (*A);
	}
	return aux;

}

t_apontador rot_esq_dir(t_apontador *A){

	(*A)->esq = rot_esq(&(*A)->esq);
	return rot_dir(&(*A));

}

t_apontador rot_dir_esq(t_apontador *A){

	(*A)->dir = rot_dir(&(*A)->dir);
	return rot_esq(&(*A));

}

t_apontador* balan_esq(t_apontador *A, int *h) {

    t_apontador f_dir;
    int fb_dir;

    switch ((*A)->fb) {
        case 1:
            (*A)->fb = 0;
            break;
        case 0:
            (*A)->fb = -1;
            *h = 0;
            break;
        case -1:
                f_dir = (*A)->dir;
                fb_dir = f_dir->fb;
                if (fb_dir <= 0) {
                    f_dir = rot_dir(&(*A));
                	if (fb_dir == 0) {
                    	(*A)->fb = -1;
                    	if(f_dir != NULL)
                    		f_dir->fb = 1;
                    	*h = 0;
                  	}
                    else {
                        (*A)->fb = 0;
                        f_dir->fb = 0;
                    }
                    (*A) = f_dir;
                }
                else {
                    (*A) = rot_dir_esq(&(*A));
                    (*A)->fb = 0;
                }
    }

    return(A);
}

t_apontador* balan_dir(t_apontador* A, int *h) {

    t_apontador f_esq;
    int fb_esq;

    switch ((*A)->fb) {
        case -1:
            (*A)->fb = 0;
            break;
        case 0:
            (*A)->fb = 1;
            *h = 0;
            break;
        case 1:
            f_esq = (*A)->esq;
            fb_esq = f_esq->fb;
            if (fb_esq >= 0) {
                f_esq = rot_esq(&(*A));
                if (fb_esq == 0) {
                    (*A)->fb = 1;
                    if(f_esq != NULL)
                    	f_esq->fb = -1;
                    *h = 0;
                }
                else {
                    (*A)->fb = 0;
                    f_esq->fb = 0;
                }
                (*A) = f_esq;
            }
            else {
                (*A) = rot_esq_dir(&(*A));
                (*A)->fb = 0;
            }
    }

    return(A);
}

t_apontador buscaRemove(t_apontador *A, t_apontador *chave, int *flag){
	
	t_apontador no_rm;
	if((*A)->esq != NULL){
		(*A)->esq = buscaRemove(&(*A)->esq, chave, flag);
		if(*flag)
			A = balan_esq(&(*A), flag);
	}
	else {
		(*chave)->item = (*A)->item;
		no_rm = (*A);
		(*A) = (*A)->dir;
		*flag = 1;
		free(no_rm);
		no_rm = NULL;
	}

	return (*A);
}

t_apontador remove_avl(t_apontador *A, int item, int *flag, int *erro){

	t_apontador aux;

	if((*A) == NULL){
		*erro = 1;
		*flag = 0;
	}
	else{
		if(item < (*A)->item){
			(*A)->esq = remove_avl(&(*A)->esq, item, flag, erro);
			if(*flag)
				A = balan_esq(&(*A), flag);
		}
		else if(item > (*A)->item){
			(*A)->dir = remove_avl(&(*A)->dir, item, flag, erro);
			if(*flag)
				A = balan_dir(&(*A), flag);
		}
		else{
			if((*A)->dir == NULL){
				aux = (*A);
				(*A) = (*A)->esq;
				free(aux);
				aux = NULL;
				*flag = 1;
			}
			else if((*A)->esq == NULL){
				aux = (*A);
				(*A) = aux->dir;
				free(aux);
				aux = NULL;
				*flag = 1;
			}
			else{
				(*A)->dir = buscaRemove(&(*A)->dir, &(*A), flag);

				if(*flag)
					A = balan_dir(&(*A), flag);
			}
		}
	}
	return (*A);
}

int remover(t_arvore *A, int item){
	
	int flag = 0, erro = 0;
	
	(*A) = remove_avl(&(*A), item, &flag, &erro);
	
	return !erro;
}

t_apontador insereItem(t_arvore *A, int C, int* flag, int* erro){

	if((*A) != NULL){
		if((*A)->item > C){
			(*A)->esq = insereItem(&(*A)->esq, C, flag, erro);
			if(*flag){
				switch((*A)->fb) {
					case -1:
						(*A)->fb = 0;
						*flag = 0;
						break;
					case 0:
						(*A)->fb = 1;
						break;
					case 1:
						if((*A)->esq->fb == 1) {
							(*A) = rot_dir(&(*A));
							(*A)->dir->fb = 0;
							(*A)->fb = 0;
						} else {
							(*A) = rot_esq_dir(&(*A));
							if((*A) != NULL){
								if((*A)->fb == 0) {
									(*A)->esq->fb = 0;
									(*A)->dir->fb = 0;
								} else if((*A)->fb == 1) {
									(*A)->esq->fb = 0;
									(*A)->dir->fb = -1;
									(*A)->fb = 0;
								} else {
									(*A)->esq->fb = 1;
									(*A)->dir->fb = 0;
									(*A)->fb = 0;
								}
							}
						}
						*flag = 0;
						break;
				}
			}
		}
		else if((*A)->item < C){
			(*A)->dir = insereItem(&(*A)->dir, C, flag, erro);
			if(*flag) {
				switch((*A)->fb) {
					case -1:
						if((*A)->dir->fb == -1) {
							(*A) = rot_esq(&(*A));
							(*A)->esq->fb = 0;
							(*A)->fb = 0;
						} else {
							(*A) = rot_dir_esq(&(*A));
							if((*A)->fb == 0) {
								(*A)->esq->fb = 0;
								(*A)->dir->fb = 0;
							} else if((*A)->fb == 1) {
								(*A)->esq->fb = 0;
								(*A)->dir->fb = -1;
								(*A)->fb = 0;
							} else {
								(*A)->esq->fb = 1;
								(*A)->dir->fb = 0;
								(*A)->fb = 0;
							}
						}
						*flag = 0;
						break;
					case 0:
						(*A)->fb = -1;
						break;
					case 1:
						(*A)->fb = 0;
						*flag = 0;
						break;
				}
			}
		}
		else{
			(*erro) = 1;
		}
	}
	else{
		(*A) = (t_apontador)malloc(sizeof(t_no));
		(*A)->item = C;
		(*A)->esq = NULL;
		(*A)->dir = NULL;
		(*A)->fb = 0;
		*flag = 1;	 
	}

	return (*A);

}

int insercao(t_arvore *A, int item){
	int flag = 0;
	int erro = 0;
	(*A) = insereItem(&(*A), item, &flag, &erro);
	return erro;
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

	criaArvore(&A);

	while(entrada != 'X'){
		scanf("%c", &entrada);
		if(entrada == 'I'){
			scanf("%d", &ent);
			if(insercao(&A, ent))
				printf("Chave existente\n");
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
			if(!remover(&A, ent)){
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