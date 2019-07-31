/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Aula 8 - Imagens

	Outubro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************************************

//TAD da quadtree

//struct que representa uma quadtree
typedef struct no {

	char item;												//item que tem em cada no'
	struct no *nordeste, *noroeste, *sudeste, *sudoeste;	//aponta para cada lugar
	int nivel;												//variavel que indica o nivel em que os itens estao

} t_no;

typedef t_no *t_apontador;
typedef t_apontador t_arvore;

/*Funcao que cria um arvore
Retorno:
	void
Parametros:
	t_arvore *A = uma arvores qualquer
*/
void criaArvore (t_arvore *A){

	*A = NULL;

}

/*Funcao que cria a raiz da arvore
Retorno:
	void
Parametros:
	t_arvore *A = uma arvores qualquer
	char item = item a ser colocado na raiz
*/
void criaRaiz(t_arvore *A, char item){

	*A = (t_apontador)calloc(1, sizeof(t_no));
	(*A)->nordeste = NULL;
	(*A)->noroeste = NULL;
	(*A)->sudeste = NULL;
	(*A)->sudoeste = NULL;
	(*A)->item = item;

}

/*Funcao que insere um item no nordeste
Retorno:
	void
Parametros:
	t_arvore *A = uma arvores qualquer
	char item = item a ser colocado na raiz
*/
void insereNordeste (t_arvore A, char item){

	criaRaiz(&A->nordeste, item);

}

/*Funcao que insere um item no noroeste
Retorno:
	void
Parametros:
	t_arvore *A = uma arvores qualquer
	char item = item a ser colocado na raiz
*/
void insereNoroeste (t_arvore A, char item){

	criaRaiz(&A->noroeste, item);

}

/*Funcao que insere um item no sudeste
Retorno:
	void
Parametros:
	t_arvore *A = uma arvores qualquer
	char item = item a ser colocado na raiz
*/
void insereSudeste (t_arvore A, char item){

	criaRaiz(&A->sudeste, item);

}

/*Funcao que insere um item no sudoeste
Retorno:
	void
Parametros:
	t_arvore *A = uma arvores qualquer
	char item = item a ser colocado na raiz
*/
void insereSudoeste (t_arvore A, char item){

	criaRaiz(&A->sudoeste, item);

}

/*Funcao que percorre a arvore em pre ordem
Retorno:
	void
Parametros:
	t_apontador A = arvore qualquer
*/
void preOrdem (t_apontador A){
	
	if(A != NULL){
		printf("%c - %d\n", A->item, A->nivel);
		preOrdem (A->nordeste);
		preOrdem (A->noroeste);
		preOrdem (A->sudeste);
		preOrdem (A->sudoeste);
	}

}

//****************************************************

/*Funcao que ajuda na alocacao nos nodos da arvore
Retorno:
	void
Parametros:
	t_arvores arvores = arvore para alocar
	int* aux = auxilia com a alocacao na arvore
	char* tree = sucetiva arvore
	int level = variavel que serve para indicar o nivel de cada item
*/
void aloca (t_arvore arvores, int* aux, char* tree, int level){

	int auxiliar;	//run codes necessita
	t_arvore A;		//auxilia com a alocacao da arvore

	if(tree[*aux] == 'p'){
		insereNordeste(arvores, tree[*aux]);
		arvores->nordeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
		A = arvores->nordeste;
		aloca(A, aux, tree, 2);
	}
	else{
		insereNordeste(arvores, tree[*aux]);
		arvores->nordeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
	}

	if(tree[*aux] == 'p'){
		insereNoroeste(arvores, tree[*aux]);
		arvores->noroeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
		A = arvores->noroeste;
		aloca(A, aux, tree, 2);
	}
	else{
		insereNoroeste(arvores, tree[*aux]);
		arvores->noroeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
	}

	if(tree[*aux] == 'p'){
		insereSudeste(arvores, tree[*aux]);
		arvores->sudeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
		A = arvores->sudeste;
		aloca(A, aux, tree, 2);
	}
	else{
		insereSudeste(arvores, tree[*aux]);
		arvores->sudeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
	}

	if(tree[*aux] == 'p'){
		insereSudoeste(arvores, tree[*aux]);
		arvores->sudoeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
		A = arvores->sudoeste;
		aloca(A, aux, tree, 2);
	}
	else{
		insereSudoeste(arvores, tree[*aux]);
		arvores->sudoeste->nivel = level;
		auxiliar  = *aux;
		*aux = auxiliar + 1;
	}

}

/*Funcao que serve para ajudar a formar a ultima arvore
Retorno:
	void
Parametros:
	t_arvore A = uma arvore
	t_arvore B = outra arvore
	t_arvore C = arvore final
*/
void criaFinal (t_arvore A, t_arvore B, t_arvore C){

	if((A->nordeste->item == 'f' && B->nordeste->item == 'e') || (A->nordeste->item == 'e' && B->nordeste->item == 'f')){
		insereNordeste(C, 'f');
		C->nordeste->nivel = 1;
	}
	else if((A->nordeste->item == 'f' && B->nordeste->item == 'p') || (A->nordeste->item == 'p' && B->nordeste->item == 'f')){
		insereNordeste(C, 'p');
		C->nordeste->nivel = 1;
		insereNordeste(C->nordeste, 'f');
		insereNoroeste(C->nordeste, 'f');
		insereSudeste(C->nordeste, 'f');
		insereSudoeste(C->nordeste, 'f');
		C->nordeste->nordeste->nivel = 2;
		C->nordeste->noroeste->nivel = 2;
		C->nordeste->sudeste->nivel = 2;
		C->nordeste->sudoeste->nivel = 2;
	}
	else if(A->nordeste->item == 'p' && B->nordeste->item == 'e'){
		insereNordeste(C, 'p');
		C->nordeste = A->nordeste;
	}
	else if(A->nordeste->item == 'e' && B->nordeste->item == 'p'){
		insereNordeste(C, 'p');
		C->nordeste = B->nordeste;
	}
	else if (A->nordeste->item == 'e' && B->nordeste->item == 'e'){
		insereNordeste(C, 'e');
		C->nordeste->nivel = 1;
	}
	else if (A->nordeste->item == 'f' && B->nordeste->item == 'f'){
		insereNordeste(C, 'f');
		C->nordeste->nivel = 1;	
	}

	if((A->noroeste->item == 'f' && B->noroeste->item == 'e') || (A->noroeste->item == 'e' && B->noroeste->item == 'f')){
		insereNoroeste(C, 'f');
		C->noroeste->nivel = 1;
	}
	else if((A->noroeste->item == 'f' && B->noroeste->item == 'p') || (A->noroeste->item == 'p' && B->noroeste->item == 'f')){
		insereNoroeste(C, 'p');
		C->noroeste->nivel = 1;
		insereNordeste(C->noroeste, 'f');
		insereNoroeste(C->noroeste, 'f');
		insereSudeste(C->noroeste, 'f');
		insereSudoeste(C->noroeste, 'f');
		C->noroeste->nordeste->nivel = 2;
		C->noroeste->noroeste->nivel = 2;
		C->noroeste->sudeste->nivel = 2;
		C->noroeste->sudoeste->nivel = 2;
	}
	else if(A->noroeste->item == 'p' && B->noroeste->item == 'e'){
		insereNoroeste(C, 'p');
		C->noroeste = A->noroeste;
	}
	else if(A->noroeste->item == 'e' && B->noroeste->item == 'p'){
		insereNoroeste(C, 'p');
		C->noroeste = B->noroeste;
	}
	else if (A->noroeste->item == 'e' && B->noroeste->item == 'e'){
		insereNoroeste(C, 'e');
		C->noroeste->nivel = 1;
	}	
	else if (A->noroeste->item == 'f' && B->noroeste->item == 'f'){
		insereNoroeste(C, 'f');
		C->noroeste->nivel = 1;	
	}

	if((A->sudeste->item == 'f' && B->sudeste->item == 'e') || (A->sudeste->item == 'e' && B->sudeste->item == 'f')){
		insereSudeste(C, 'f');
		C->sudeste->nivel = 1;
	}
	else if((A->sudeste->item == 'f' && B->sudeste->item == 'p') || (A->sudeste->item == 'p' && B->sudeste->item == 'f')){
		insereSudeste(C, 'p');
		C->sudeste->nivel = 1;
		insereNordeste(C->sudeste, 'f');
		insereNoroeste(C->sudeste, 'f');
		insereSudeste(C->sudeste, 'f');
		insereSudoeste(C->sudeste, 'f');
		C->sudeste->nordeste->nivel = 2;
		C->sudeste->noroeste->nivel = 2;
		C->sudeste->sudeste->nivel = 2;
		C->sudeste->sudoeste->nivel = 2;
	}
	else if(A->sudeste->item == 'p' && B->sudeste->item == 'e'){
		insereSudeste(C, 'p');
		C->sudeste = A->sudeste;
	}
	else if(A->sudeste->item == 'e' && B->sudeste->item == 'p'){
		insereSudeste(C, 'p');
		C->sudeste = B->sudeste;
	}
	else if (A->sudeste->item == 'e' && B->sudeste->item == 'e'){
		insereSudeste(C, 'e');
		C->sudeste->nivel = 1;
	}	
	else if (A->sudeste->item == 'f' && B->sudeste->item == 'f'){
		insereSudeste(C, 'f');
		C->sudeste->nivel = 1;	
	}

	if((A->sudoeste->item == 'f' && B->sudoeste->item == 'e') || (A->sudoeste->item == 'e' && B->sudoeste->item == 'f')){
		insereSudoeste(C, 'f');
		C->sudoeste->nivel = 1;
	}
	else if((A->sudoeste->item == 'f' && B->sudoeste->item == 'p') || (A->sudoeste->item == 'p' && B->sudoeste->item == 'f')){
		insereSudoeste(C, 'p');
		C->sudoeste->nivel = 1;
		insereNordeste(C->sudoeste, 'f');
		insereNoroeste(C->sudoeste, 'f');
		insereSudeste(C->sudoeste, 'f');
		insereSudoeste(C->sudoeste, 'f');
		C->sudoeste->nordeste->nivel = 2;
		C->sudoeste->noroeste->nivel = 2;
		C->sudoeste->sudeste->nivel = 2;
		C->sudoeste->sudoeste->nivel = 2;
	}
	else if(A->sudoeste->item == 'p' && B->sudoeste->item == 'e'){
		insereSudoeste(C, 'p');
		C->sudoeste = A->sudoeste;
	}
	else if(A->sudoeste->item == 'e' && B->sudoeste->item == 'p'){
		insereSudoeste(C, 'p');
		C->sudoeste = B->sudoeste;
	}
	else if (A->sudoeste->item == 'e' && B->sudoeste->item == 'e'){
		insereSudoeste(C, 'e');
		C->sudoeste->nivel = 1;
	}	
	else if (A->sudoeste->item == 'f' && B->sudoeste->item == 'f'){
		insereSudoeste(C, 'f');
		C->sudoeste->nivel = 1;	
	}

}

/*Funcao que cantabiliza o numero de pixels pretos pela pre ordem
Retorno:
	void
Parametros:
	t_arvore A = uma arvore
	int* resul = guarda o resultado
*/
void computa(t_arvore A, int* resul){

	int aux = 0; 		//ajuda no calculo

	if(A != NULL){
		if(A->item == 'f' && A->nivel == 1){
			aux = *resul;
			*resul = aux + 256;
		}
		else if(A->item == 'f' && A->nivel == 2){
			aux = *resul;
			*resul = aux + 64;
		}
		computa (A->nordeste, resul);
		computa (A->noroeste, resul);
		computa (A->sudeste, resul);
		computa (A->sudoeste, resul);
	}

}

/*Funcao que cria uma arvore resultado e computa o numero de pixels pretos
Retorno:
	int = o numero de pixels pretos
Parametros:
	t_arvore A = uma arvore
	t_arvore B = outra arvore
*/
int calcula(t_arvore A, t_arvore B){

	t_arvore C;			//arvore final

	criaArvore(&C);

	criaRaiz(&C, 'p');
	C->nivel = 0;

	criaFinal(A, B, C);

	int resul = 0;		//guarda o resultado

	computa(C, &resul);

	return resul;

}

/*Funcao que cria as arvores para fazer a sobreposicao posteriormente
Retorno:
	void;
Paramentos:
	char** arvores = sucetivas arvores
	int* pixel_preto = quantidade de pixels pretos na imagem final
*/
void cria_quad (char** arvores, int* pixel_preto){

	t_arvore arvore_um;			//primeira arvore
	t_arvore arvore_dois;		//segunda arvore
	int aux = 0;				//auxilia com a passagem pelo vetor do caso da arvore

	criaArvore (&arvore_um);
	criaArvore (&arvore_dois);

	criaRaiz(&arvore_um, arvores[0][aux]);
	arvore_um->nivel = 0;
	aux++;
	aloca(arvore_um, &aux, arvores[0], 1);

	aux = 0;

	criaRaiz(&arvore_dois, arvores[1][aux]);
	arvore_dois->nivel = 0;
	aux++;
	aloca(arvore_dois, &aux, arvores[1], 1);

	*pixel_preto = calcula(arvore_um, arvore_dois);

}

//****************************************************

int main () {

	int N;				//quantidade de casos testes
	int pixel_preto;	//quantidade de pixels pretos na imagem final
	int imagem = 0;		//guarda os casos
	char** arvores;		//sucetivas arvores

	//entrada do numero de casos testes
	scanf("%d", &N);
	getchar();

	//alocacao na heap das arvores
	arvores = (char**)calloc(2, sizeof(char*));
	for(int cont = 0; cont < 2; cont++){
		arvores[cont] = (char*)calloc(100, sizeof(char));
	}

	for (int cont = 0; cont < 2 * N; cont += 2){
		for(int cont1 = 0; cont1 < 2; cont1++){
			if(cont1 == 0){
				arvores[0][0] = '\0';
				arvores[1][0] = '\0';
				imagem++;
			}
			//entrada das arvores
			fgets(arvores[cont1], 100, stdin);
			//retira a quebra de linha
			if(arvores[cont1][strlen(arvores[cont1]) - 1] == '\n'){
				arvores[cont1][strlen(arvores[cont1]) - 1] = '\0';
			}
			if(cont1 == 1){
				cria_quad(arvores, &pixel_preto);
				printf("%d %d pixels pretos.\n", imagem, pixel_preto);
			}
		}
	}

	for(int cont2 = 0; cont2 < 2; cont2++){
		free(arvores[cont2]);
	}
	free(arvores);

	return 0;

}