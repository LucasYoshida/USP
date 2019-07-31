/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Trabalho III - Parser de JSON

	Setembro - 2017

	Lucas Noriyuki Yoshida - 10262586

***************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*struct que serve para contagem de tokens e alguns nao terminais
encontrados até o momento do erro (considerando apenas como 'token')*/
typedef struct tokens_e_nao_terminais{
	int o;		//objects
	int a;		//arrays
	int p;		//pairs
	int s;		//strings
	int n;		//numbers
	int t;		//trues
	int f;		//falses
	int null;	//nulls
} token;

//*************************************************

/*Funcao que verifica o proximo caracter de uma entrada
Retorno:
	int == '0' -> nao deu erro
	int == '1' -> deu erro
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	int proximo == proxima casa a ser verificada
*/
int verifica_proximo(char* entrada, int proximo){

	//depois do '\'que sao proibidos
	if(entrada[proximo] == 'b' || entrada[proximo] == 'f' ||entrada[proximo] == 'n' || entrada[proximo] == 'r' ||entrada[proximo] == 't' || entrada[proximo] == 'u' ||entrada[proximo] == '"' || (int)entrada[proximo] == 92){
		return 1;
	}
	else{
		return 0;
	}

}

/*Funcao que acha o numero de strings nas frases
Retorno:
	int == '0' -> nao deu erro
	int == '1' -> deu erro
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	token* saida == tokens e alguns nao terminais necessarios para saida
	int inicio == inicio para verificar a linha
*/
int acha_string(char* entrada, token* saida, int* inicio){

	int erro = 0;				//verifica se tem erro
	int ajuda = *inicio;		//ajuda na verificacao do vetor
	int cont = 0;				//contador pelo vetor

	//caso ' """ '
	if(entrada[ajuda-1] == '"' && entrada[ajuda + 1] == '"' && entrada[ajuda] == '"'){
		return 1;
	}

	//ate o fim da frase
	for(cont = ajuda; cont < strlen(entrada); cont++){
		*inicio = cont;
		//caso encontrar uma '\'
		if((int)entrada[cont] == 92){
			erro = verifica_proximo(entrada, cont + 1);
			if(erro > 0){
				return 1;
			}
		}
		//caso encontre o fim da string
		else if(entrada[cont] == '"'){
			*inicio = cont + 1;
			saida->s++;
			return 0;
		}
	}

	//caso nao encontrar o fim da string
	return 1;

}

//chamada da funcao 'acha_value' necessaria para o funcionamento de acha_pair
int acha_value(char* entrada, token* saida, int* inicio);

/*Funcao que acha o numero de pairs nas frases
Retorno:
	int == '0' -> nao deu certo
	int == '1' -> deu certo
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	token* saida == tokens e alguns nao terminais necessarios para saida
	int inicio == inicio para verificar a linha
*/
int acha_pair(char* entrada, token* saida, int* inicio){

	int erro = 0;		//verifica se tem erro
	int aux = 0;		//ajuda com o inicio das funcoes

	//incrementa o *inicio para pegar logo apos as '"'
	aux = *inicio;
	*inicio = aux + 1;

	//verifica a string esta correta
	erro = acha_string(entrada, saida, inicio);
	if(erro > 0){
		return 1;
	}
	else{
		//se a string estiver correta verifica se o proximo caracter e' ':'
		if(entrada[*inicio] == ':'){
			aux = *inicio;
			*inicio = aux + 1;
			//verifica o value esta correto
			erro = acha_value(entrada, saida, inicio);
			if(erro > 0){
				return 1;
			}
			else if (*inicio < strlen(entrada) - 1){
				saida->p++;
				return 0;
			}
			saida->p++;
		}
		else{
			return 1;
		}
	}

	return 0;

}

/*Funcao que acha o numero de objects nas frases
Retorno:
	int == '0' -> nao deu erro
	int == '1' -> deu erro
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	token* saida == tokens e alguns nao terminais necessarios para saida
	int inicio == inicio para verificar a linha
*/
int acha_object(char* entrada, token* saida, int* inicio){

	int cont = *inicio;		//ajuda na verificacao do vetor
	int erro = 0;			//verifica se tem erro

	//ate o fim do object
	while(entrada[cont] != '}'){
		//ignora a virgula
		if(entrada[cont] != ',' && entrada[cont] != '}'){
			*inicio = cont;
			//verifica se o pair esta correto
			erro = acha_pair(entrada, saida, inicio);
			if(erro == 1){
				return 1;
			}
			else{
				cont = *inicio;
				cont--;
			}
		}
		cont++;
	}

	saida->o++;
	cont = *inicio;
	*inicio = cont + 1;
	return 0;
}

/*Funcao que acha o numero de arrays nas frases
Retorno:
	int == '0' -> nao deu erro
	int == '1' -> deu erro
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	token* saida == tokens e alguns nao terminais necessarios para saida
	int inicio == inicio para verificar a linha
*/
int acha_array(char* entrada, token* saida, int* inicio){

	int cont = *inicio;		//ajuda na verificacao do vetor
	int erro = 0;			//verifica se tem erro

	//ate o fim do array
	while(entrada[cont] != ']'){
		//acha um pair
		if(entrada[cont] == ':'){
			return 1;
		}
		//quando nao tem uma virgula dividindo os values
		else if(entrada[cont] != ','){
			*inicio = cont;
			//verifica o value esta correto
			erro = acha_value(entrada, saida, inicio);
			if(erro == 1){
				return 1;
			}
			else{
				cont = *inicio;
				cont--;
			}
		}
		cont++;
	}

	saida->a++;

	cont = *inicio;
	*inicio = cont + 1;

	return 0;

}

/*Funcao que acha o numero de numeros nas frases
Retorno:
	int == '0' -> nao deu erro
	int == '1' -> deu erro
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	token* saida == tokens e alguns nao terminais necessarios para a saida
	int* inicio == inicio para verificar a linha
*/
int acha_numero(char* entrada, token* saida, int* inicio){
	
	int cont = *inicio;
	
	//caso o numero comece com '.' ou 'e' ou 'E'
	if(entrada[cont] == '.' || entrada[cont] == 'e' || entrada[cont] == 'E'){
		return 1;
	}

	//caso o numero so tenha sinal ('+' ou '-')
	if((entrada[cont] == '+' || entrada[cont] == '-') && (entrada[cont+1] == '}' || entrada[cont+1] == ']')){
		return 1;
	}

	//so vai ser numero se forem esses caracteres
	while(entrada[cont] == '-' || entrada[cont] == '.' || entrada[cont] == '+' || entrada[cont] == 'e' || entrada[cont] == 'E' || ((int)entrada[cont] - 48 >= 0 && (int)entrada[cont] - 48 <= 9)){
		//acha o sinal (caso tenha)
		if(entrada[cont] == '-' || entrada[cont] == '+'){
			cont++;
		}
		//caso seja digito (0 ~ 9)
		else if((int)entrada[cont] - 48 >= 0 && (int)entrada[cont] - 48 <= 9){
			cont++;
		}
		//caso seja expoente (E ou e)
		else if(entrada[cont] == 'E' || entrada[cont] == 'e'){
			cont++;
			//caso tenha sinal
			if(entrada[cont] == '-' || entrada[cont] == '+'){
				cont++;
			}
			//caso seja digito
			else if((int)entrada[cont] - 48 >= 0 && (int)entrada[cont] - 48 <= 9){
				cont++;
			}
			//nao pode ter outro expoente em seguida
			else if(entrada[cont] == 'e' || entrada[cont] == 'E'){
				return 1;
			}
			else{
				return 1;
			}
		}
		//caso seja fracionario
		else if(entrada[cont] == '.'){
			cont++;
			//caso seja digito
			if((int)entrada[cont] - 48 >= 0 && (int)entrada[cont] <= 9){
				cont++;
			}
		}
	}

	*inicio = cont;

	saida->n++;

	return 0;

}

/*Funcao que acha um value nas frases
Retorno:
	int == '0' -> nao deu erro
	int == '1' -> deu erro
Parametros:
	char* entrada == vetor que guarda uma entrada do problema
	token* saida == tokens e alguns nao terminais necessarios para saida
	int inicio == inicio para verificar a linha
*/
int acha_value(char* entrada, token* saida, int* inicio){

	int ajuda = *inicio;		//ajuda na verificacao do vetor
	int erro = 0;				//verifica se tem erro

	//caso encontre outro object
	if(entrada[ajuda] == '{'){
		*inicio = ajuda + 1;
		return acha_object(entrada, saida, inicio);
	}
	//caso encontre um outro array
	else if(entrada[ajuda] == '['){
		*inicio = ajuda + 1;
		return acha_array(entrada, saida, inicio);
	}
	//caso encontre uma string
	else if(entrada[ajuda] == '"'){
		*inicio = ajuda + 1;
		//verifica se a string esta correta
		erro = acha_string(entrada, saida, inicio);
		if(erro > 0){
			return 1;
		}
		else{
			//caso participe de um array
			if(entrada[*inicio] == ',' || entrada[*inicio] == ']'){
				return 0;
			}
			//caso participe de um object
			else if(entrada[*inicio] == ':' || entrada[*inicio] == '}'){
				return 0;
			}
		}	
	}
	//caso encontre um 'true'
	else if(entrada[ajuda] == 't'){
		//so pode possuir a palavra 'true'
		if(entrada[*inicio + 4] != '}' && entrada[*inicio + 4] != ']' && entrada[*inicio + 4] != ','){
			return 1;
		}
		*inicio = ajuda + 4;
		saida->t++;
		return 0;			
	}
	//caso encontre um 'false'
	else if(entrada[ajuda] == 'f'){
		//so pode possuir a palavra 'false'
		if(entrada[*inicio + 5] != '}' && entrada[*inicio + 5] != ']' && entrada[*inicio + 5] != ','){
			return 1;
		}
		*inicio = ajuda + 5;
		saida->f++;
		return 0;			
	}
	//caso encontre um 'null'
	else if(entrada[ajuda] == 'n'){
		//so pode possuir a palavra 'null'
		if(entrada[*inicio + 4] != '}' && entrada[*inicio + 4] != ']' && entrada[*inicio + 4] != ','){
			return 1;
		}
		*inicio = ajuda + 4;
		saida->null++;
		return 0;			
	}
	//caso for um numero
	else{
		*inicio = ajuda;
		//verifica se o nmumero esta correto
		erro = acha_numero(entrada, saida, inicio);
		if(erro > 0){
			return 1;
		}
		else{
			//caso participe de um array
			if(entrada[*inicio] == ',' || entrada[*inicio] == ']'){
				return 0;
			}
			//caso participe de um object
			else if(entrada[*inicio] == '}'){
				return 0;
			}
		}
	}

	return 0;

}

/*Funcao que serve para printar a saida
Retorno:
	void
Parametros:
	token saida == tokens e algusn nao terminais necessarios para saida
	int erro == serve para dizer em qual linha tem erro (se tiver)
*/
void printar(token saida, int erro){

	//se tem erro (erro > 0) printa
	if(erro > 0){
		printf("Error line %d\n", erro);
	}

	//printar objects
	printf("Number of Objects: %d\n", saida.o);

	//printar arrays
	printf("Number of Arrays: %d\n", saida.a);

	//printar pairs
	printf("Number of Pairs: %d\n", saida.p);

	//printar strings
	printf("Number of Strings: %d\n", saida.s);

	//printar numbers
	printf("Number of Numbers: %d\n", saida.n);

	//printar trues
	printf("Number of Trues: %d\n", saida.t);

	//printar falses
	printf("Number of Falses: %d\n", saida.f);

	//printar nulls
	printf("Number of Nulls: %d\n", saida.null);

}

//*************************************************

int main() {

	char** entrada;			//matriz que guarda as entradas do problema
	int frases = 0;			//contador que guarda a quantidade de frases
	token saida = {0};		//tokens e alguns nao terminais necessarios para saida
	int erro = 0;			//serve para dizer em qual linha tem erro (se tiver)

	//malloc das entradas
	entrada = (char**)calloc(3, sizeof(char*));
	for(int cont = 0; cont < 3; cont++){
		entrada[cont] = (char*)calloc(500, sizeof(char));
	}

	//verifica a quantidade de frases e armazena as mesmas
	for(int cont = 0; cont < 3; cont++){
		//entrada das frases
		fgets(entrada[cont], 500, stdin);
		frases++;
		//retira os espaços
		for(int cont1 = 0; cont1 < strlen(entrada[cont]); cont1++){
			if((int)entrada[cont][cont1] == 32){
				for(int cont2 = cont1 + 1; cont2 <= strlen(entrada[cont]); cont2++){
					entrada[cont][cont2-1] = entrada[cont][cont2];
				}
				cont1--;
			}
		}
		//retira a quebra de linha
		if(entrada[cont][strlen(entrada[cont]) - 1] == '\n'){
			entrada[cont][strlen(entrada[cont])-1] = '\0';
		}
		else{
			break;
		}
	}

	int aux = 0;		//ajuda a guardar o erro
	int cont = 0;		//contador para as frases

	//verifica cada frase da entrada
	for(cont = 0; cont < frases; cont++){
		int inicio = 1;			//inicio da analise
		if(entrada[cont][0] == '['){
			aux = acha_array(entrada[cont], &saida, &inicio);
			if(aux > 0){
				erro = cont + 1;
				break;
			}
		}
		else if(entrada[cont][0] == '{'){
			aux = acha_object(entrada[cont], &saida, &inicio);
			if(aux > 0){
				erro = cont + 1;
				break;
			}
		}
	}

	printar(saida, erro);

	//freees
	for(int cont = 0; cont < 3; cont++){
		free(entrada[cont]);
	}
	free(entrada);

	return 0;

}