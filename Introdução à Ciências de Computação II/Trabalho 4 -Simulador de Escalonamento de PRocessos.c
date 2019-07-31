/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Trabalho 4 - Simulador de Escalonador de Processos

	Outubro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_MAX 1000

//*****************TAD LISTA CIRCULAR*********************

struct listac{

	int item;
	struct listac *prox;
};

typedef struct listac t_lista;

/*Funcao que inicializa uma lista circular
Retorno:
	t_lista* = lista criada
Parametros:
	int item = item para iniciar a lista
*/
t_lista* inicializaLista (int item){

	t_lista* A = (t_lista*)malloc(sizeof(t_lista));
	A->item = item;
	A->prox = A;
	return A;

}

/*Funcao que insere um item na lista circular
Retorno:
	void
Parametros:
	t_lista* lista = uma lista qualquer
	t_item item = item a ser colocado na lista
*/
void insereLista (t_lista *lista, int item){

    t_lista* A;

    for(A = lista; A->prox != lista; A = A->prox);
    A = A->prox = (t_lista*)calloc(1, sizeof(t_lista));
    A->item = item;
    A->prox = lista;
    A = NULL;

}

/*Funcao que retira um item na lista circular
Retorno:
	void
Parametros:
	t_lista* lista = uma lista qualquer
	int item = mostra o item a ser retirado
*/
t_lista* retiraLista (t_lista *lista, int item){

	//se a lista tem so' um elemento
    if(item == lista->item && lista->prox == lista){
        free(lista);
        lista = NULL;
        return NULL;
    }

    t_lista* A = lista;

    //para retirar no inicio da lista
    if(item == lista->item && lista->prox != lista){
        for(; A->prox != lista; A = A->prox);
        A->prox = lista->prox;
        t_lista* B = lista;
        lista = lista->prox;
        free(B);
        B = A = NULL;
        return lista;
    }

    //outras localizacoes
    do{
    	if(A->prox->item == item){
    		t_lista* C = A->prox;
       		A->prox = A->prox->prox;
            free(C);
            C = NULL;
            break;
        }
        A = A->prox;
    } while(A != lista);

    A = NULL;

    return lista; //e retornamos a nossa nova lista

}

/*Funcao que mostra os itens da lista circular
Retorno:
	void
Parametros:
	t_lista* lista = uma lista qualquer
*/
void mostraLista(t_lista *lista){

    t_lista* loop = lista;

    do{
        printf("%d ", loop->item);
        loop = loop->prox;
    } while(loop != lista);

    printf("\n");

}

//*****************TAD FILA*********************

//struct que representa uma implementacao de uma fila
typedef struct {

	int item[TAM_MAX];		//itens da fila
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
void retiraFila (t_fila* A){

	for(int cont = 0; cont < (*A).fim - 1; cont++){
		(*A).item[cont] = (*A).item[cont + 1];
	}
	//coloca um '\0' no lugar (como se fosse um NULL)
	(*A).item[(*A).fim] = '\0';
	(*A).fim--;

}

/*Funcao que inicializa a fila 
Retorno:
	void
Parametros:
	t_fila* A = uma fila qualquer
*/
void inicializaFila (t_fila* A){

	for(int cont = 0; cont < TAM_MAX; cont++){
		(*A).item[cont] = 0;
	}

	(*A).inicio = 0;
	(*A).fim = 0;

}


//******************STRUCTS MAIN*********************

//struct que representa os diferentes tipos de tempo
typedef struct temp{

	int ini;		//tempo inicial de entrada no simulador
	int fin;		//volume de 'quanta' necessario para se completamente executado

} temp;

//struct que representa a formulacao da entrada 
typedef struct process{

	temp t;			//tempos da stuct acima
	int p;			//processo a ser simulado
	int r;			//prioridade

} process;

//******************FUNCOES MAIN**********************

/*Funcao que transforma um numero string em int
Retorno:
	int = o proprio numero
Parametro:
	char* numero = numero em formato de string
*/
int transforma (char* numero){

	int aux = 0;		//auxilia com a soma para formar o numero final
	int aux1 = 1;		//auxilia para ver a ordem das casas decimais
	int aux2 = 0;		//auxilia na contagem

	for(int cont = 0; cont < strlen(numero); cont++){
		aux2 = aux;
		aux = ((numero[cont] - 48) * pow(10, strlen(numero) - aux1)) + aux2;
		aux1++;
	}

	return aux;

}

/*Funcao que transforma a entrada em string para numeros em int para Round Robin
Retorno:
	void
Parametros:
	process* processos = processo/tempo/prioridade da entrada
	char** entrada = entrada em char para depois ser passada em int
	int num = numero de processos a serem simulados
*/
void para_round (process* processos, char** entrada, int num){

	char** numeros;			//numeros em formato de string quebrando em menores
	int contador = 0;		//contador que auxilia na alocacao dos processos em int

	for(int cont = 0; cont < num; cont++){
		//cria uma matriz auxiliar para strings auxiliares representando numeros
		numeros = (char**)calloc(4, sizeof(char*));
		for(int cont1 = 0; cont1 < 4; cont1++){
			numeros[cont1] = (char*)calloc(5, sizeof(char));
		}
		int aux = 0;			//auxilia com a alocacao das linhas
		int aux1 = 0;			//auxilia com a alocacao das colunas
		for(int cont1 = 0; cont1 < strlen(entrada[cont]); cont1++){
			if(entrada[cont][cont1] != ' ' && (int)entrada[cont][cont1] != 13){
				numeros[aux][aux1] = entrada[cont][cont1];
				aux1++; 
			}
			else{
				aux++;
				aux1 = 0;
			}
		}
		processos[contador].p = transforma(numeros[0]);
		processos[contador].t.ini = transforma(numeros[1]);
		processos[contador].t.fin = transforma(numeros[2]);
		processos[contador].r = transforma(numeros[3]);
		contador++;
		for(int cont1 = 0; cont1 < 4; cont1++){
			free(numeros[cont1]);
		}
		free(numeros);
	}

}

/*Funcao que transforma a entrada em string para numeros em int para FIFO
Retorno:
	void
Parametros:
	process* processos = processo/tempo da entrada
	char** entrada = entrada em char para depois ser passada em int
	int num = numero de processos a serem simulados
*/
void para_FIFO (process* processos, char** entrada, int num){

	char** numeros;			//numeros em formato de string quebrando em menores
	int contador = 0;		//contador que auxilia na alocacao dos processos em int

	for(int cont = 1; cont < num; cont++){
		//cria uma matriz auxiliar para strings auxiliares representando numeros
		numeros = (char**)calloc(3, sizeof(char*));
		for(int cont1 = 0; cont1 < 3; cont1++){
			numeros[cont1] = (char*)calloc(5, sizeof(char));
		}
		int aux = 0;			//auxilia com a alocacao das linhas
		int aux1 = 0;			//auxilia com a alocacao das colunas
		for(int cont1 = 0; cont1 < strlen(entrada[cont]); cont1++){
			if(entrada[cont][cont1] != ' ' && (int)entrada[cont][cont1] != 13){
				numeros[aux][aux1] = entrada[cont][cont1];
				aux1++; 
			}
			else{
				aux++;
				aux1 = 0;
			}
		}
		processos[contador].p = transforma(numeros[0]);
		processos[contador].t.ini = transforma(numeros[1]);
		processos[contador].t.fin = transforma(numeros[2]);
		contador++;
		for(int cont1 = 0; cont1 < 3; cont1++){
			free(numeros[cont1]);
		}
		free(numeros);
	}

}

/*Funcao que ordena os processos para FIFO
Retorno:
	void
Parametros:
	process* processos = processo/tempo da entrada
	int num = numero de processos a serem simulados
*/
void ordenaFIFO (process* processos, int num){

	//utiliza o metodo de bubble sort
	for(int fim = num - 1; fim > 0; fim--){
		for(int cont = 0; cont < fim; cont++){
			if(processos[cont].t.ini > processos[cont + 1].t.ini){
				process aux = processos[cont];
				processos[cont] = processos[cont + 1];
				processos[cont + 1] = aux;
			}
			else if(processos[cont].t.ini == processos[cont + 1].t.ini){
				if(processos[cont].p > processos[cont + 1].p){
					process aux = processos[cont];
					processos[cont] = processos[cont + 1];
					processos[cont + 1] = aux;
				}
			}
		}
	}

}

/*Funcao que computa FIFO
Retorno:
	void
Parametros:
	process* processos = processo/tempo da entrada
	int num = numero de processos a serem simulados
*/
void computaFIFO (process* processos, int num){

	//no FIFO nao existe prioridade, portanto vai acrescentando na fila
	//a partir do tempo e o numero do processo em ordem crescente

	ordenaFIFO(processos, num);

	t_fila calc;		//fila que serve para o calculo dos processos
	
	inicializaFila(&calc);

	//cria um tempo de execucao maxima
	for(int temp = 1; temp < 100; temp++){
		for(int cont = 1; cont < num; cont++){
			//coloca os processos na fila em forma de cada item repitido e passa por eles conforme o tempo
			if(temp == processos[cont].t.ini){
				for(int cont1 = 0; cont1 < processos[cont].t.fin; cont1++){
					insereFila(&calc, processos[cont].p);
				}
			}
		}
		//quando o item do inicio nao for igual ao proximo item quer dizer q o processo acabou
		//ou quando o indicador de inicio for igual ao do fim
		if(calc.item[calc.inicio] != calc.item[calc.inicio + 1] || calc.inicio == calc.fim){
			printf("%d %d\n", calc.item[calc.inicio], temp);
		}
		retiraFila(&calc);
		//para quando a fila estiver vazia
		if(calc.item[calc.inicio] == '\0'|| calc.inicio == calc.fim){
		 	printf("%d %d\n", calc.item[calc.inicio], temp);
			break;
		}
	}

}

/*Funcao que ordena (pelo menos para primeira iteracao) os processos para ROUND-ROBIN
Retorno:
	void
Parametros:
	process* processos = processos/tempo/prioridade da entrada
	int num = numero de processos a serem simulados
*/
void ordenaROUND (process* processos, int num){

	/*atribui um valor muito alto para a prioridade '0'
	assim facilita na ordenacao, pois o processo com 
	valor '0' deve vir primeiro e ser executado inteiramente
	antes dos outros no fim desta funcao o valor volta a ser '0'*/

	for(int cont = 0; cont < num; cont++){
		if(processos[cont].r == 0){
			processos[cont].r = TAM_MAX;
		}
	}

	//faz um bubble sort
	for(int fim = num - 1; fim > 0; fim--){
		for(int cont = 0; cont < fim; cont++){
			if(processos[cont].t.ini > processos[cont + 1].t.ini){
				process aux = processos[cont];
				processos[cont] = processos[cont + 1];
				processos[cont + 1] = aux;
			}
			else if(processos[cont].t.ini == processos[cont + 1].t.ini){
				if(processos[cont].r < processos[cont + 1].r){
					process aux = processos[cont];
					processos[cont] = processos[cont + 1];
					processos[cont + 1] = aux;
				}
				else if(processos[cont].r == processos[cont + 1].r){
					if(processos[cont].p > processos[cont + 1].p){
						process aux = processos[cont];
						processos[cont] = processos[cont + 1];
						processos[cont + 1] = aux;		
					}
				}
			}
		}
	}

	for(int cont = 0; cont < num; cont++){
		if(processos[cont].r == TAM_MAX){
			processos[cont].r = 0;
		}
	}
	
}

/*Funcao que computa ROUND-ROBIN
Retorno:
	void
Parametros:
	process* processos = processos/tempo/prioridade da entrada
	int num = numero de processos a serem simulados
*/
void computaROUND (process* processos, int num){

	//no ROUND-ROBIN o mais importante e' o tempo em que o processos
	//entra pra ser executado/simulado e so' depois e' visto a prioridade
	//exceto quando a prioridade e' '0', pois faz como se fosse FIFO

	ordenaROUND(processos, num);

	t_lista* calc;			//lista que serve para o calculo dos processos
	int proximo = 0;		//mostra se o proximo e' necessario pegar o proximo item da lista
	int prioridade = -1;	//indica se tem algum processo com prioridade '0'
	int adicionados = 0;	//inidica quantos itens foram adicionados na lista
	int tempo = 0;			//indica o proximo maior tempo, quando tiver
	int aux;				//guarda o item em que o novo ciclo deve comecar
	int aux1;				//guarda a posicao do item acima em 'processos'
	int passou = 0;			//indica se passou por um dos if's
	int atuais = 0;   		//mostra a quantidade de itens atuais na lista

	//esta funcao cria uma nova lista quando um novo processo eh chamado
	//caso esse esteja com tempo inicial diferente dos outros

	//cria um tempo de execucao maxima
	for(int temp = 1; temp < 100; temp++){
		for(int cont = 0; cont < num; cont++){
			if(temp == processos[cont].t.ini && processos[cont].t.fin > 0){
				if(cont == 0){
					//ja deixa criado e alocado um item
					calc = inicializaLista(processos[cont].p);
					adicionados++;
					atuais++;
					//verifica a prioridade '0'
					if(processos[cont].r == 0){
						prioridade = cont;
					}
				}
				else{
					insereLista(calc, processos[cont].p);
					adicionados++;
					atuais++;
					//verifica a prioridade '0'
					if(processos[cont].r == 0){
						prioridade = cont;
					}
				}
			}
		}

		//verifica se passou no ultimo for desta funcao e com isso regula
		//qual ira ser o 'comeco' da nova lista
		if(passou == 1){
			for(int cont = 0; cont < num; cont++){
				if(calc->item == aux){
					break;
				}
				else{
					calc = calc->prox;
				}
			}
			passou = 0;
		}

		//verifica se tem um novo processo a ser executado em outro tempo
		if(processos[adicionados].t.ini == temp + 1){
			tempo = 1;
		}

		//caso tenha prioridade maior que '0'
		if(prioridade >= 0){
			processos[prioridade].t.fin--;
			//quando chega no fim da execucao
			if(processos[prioridade].t.fin == 0){
				calc = retiraLista(calc, processos[prioridade].p);
				atuais--;
				printf("%d %d\n", processos[prioridade].p, temp);
				prioridade = -1;
			}
		}
		//caso seja prioridade '0'
		else{
			//executa como se fosse im FIFO
			for(int cont = 0; cont < num; cont++){
				if((*calc).item == processos[cont].p && processos[cont].t.fin > 0){
					processos[cont].t.fin--;
					if(processos[cont].t.fin == 0){
						calc = retiraLista(calc, processos[cont].p);
						atuais--;
						printf("%d %d\n", processos[cont].p, temp);
						proximo = 1;
						if(calc == NULL){
							return;
						}
						else{
							break;
						}
					}
				}
			}
			//so vai ir para o proximo processo quando terminar o de prioridade '0'
			if(proximo == 0){
				calc = calc->prox;
			}
			proximo = 0;
		}

		//verifica se existe um novo processo a ser colocado na lista
		//sendo que este deve ter tempo inicial diferente dos outros
		if(tempo == 1){
			passou = 1;
			int aux2 = 0;		//serve para ver onde o novo processo ira ficar na lista com base na sua prioridade
			aux = calc->item;
			for(int cont = 0; cont < num; cont++){
				if(processos[cont].p == aux){
					aux1 = cont;
				}
			}
			//quando o processo esta prestes a sair da lista
			if(processos[aux1].t.fin == 1){
			  aux2 = -1;
			  processos[aux1].r = 10;
			}
			//retira todos os processos da lista para inseri-los de forma correta posteriormente
			for(int cont = 0; cont < atuais; cont++){
				calc = retiraLista(calc, processos[cont].p);
			}
			//aumenta o tempo inicil de forma que facilite a ordenacao
			for(int cont = 0; cont < adicionados; cont++){
				processos[cont].t.ini = temp + 1;
			}
			//verifica se e' a maior prioridade
			for(int cont = 0; cont < num; cont++){
	  			if(processos[adicionados].r >= processos[cont].r){
		  		   	aux2++;
		  		}
			}
			if(aux2 == num){
				aux = processos[adicionados].p;
			}
			ordenaROUND(processos, num);
			//acha a posicao de 'aux' em 'processos' 
			for(int cont = 0; cont < num; cont++){
				if(processos[cont].p == aux){
					aux1 = cont;
				}
			}
			//caso nenhum daqueles demonstre verdadeiro, sobra este que verifica se o proximo tem prioridade maior
			if(processos[adicionados].r > processos[aux1].r && aux2 != num){
			  aux = processos[aux1].p;
			}
			atuais = 0;
			tempo = 0;
			adicionados = 0;
		}
	}

}

//*****************MAIN**********************

int main () {

	process* processos; 			//processo/tempo/prioridade da entrada
	char** entrada;					//entrada em char para depois ser passada em int
	int num = 0;					//numero de processos a serem simulados

	//alocacao dinamica
	processos = (process*)calloc(10, sizeof(process));
	entrada = (char**)calloc(10, sizeof(char*));
	for(int cont = 0; cont < 10; cont++){
		entrada[cont] = (char*)calloc(100, sizeof(char));
	}

	//pega a entrada em formato char
	for(int cont = 0; cont < 10; cont++){
		num++;			//contador dos processos
		//entrada dos processos
		fgets(entrada[cont], 100, stdin);
		//retira a quebra de linha
		if(entrada[cont][strlen(entrada[cont]) - 1] == '\n'){
			entrada[cont][strlen(entrada[cont]) - 1] = '\0';
		}
		else{
			break;
		}
	}

	//transforma a entrada char em int
	if(entrada[0][0] == 'f'){
		para_FIFO(processos, entrada, num);
		computaFIFO(processos, num);
	}
	else{
		para_round(processos, entrada, num);
		computaROUND(processos, num);
	}

	//frees
	free(processos);
	for(int cont = 0; cont < 10; cont++){
		free(entrada[cont]);
	}
	free(entrada);

	return 0;

}