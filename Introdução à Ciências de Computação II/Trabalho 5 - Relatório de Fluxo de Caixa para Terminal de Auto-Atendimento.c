/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Trabalho 5 - Relatorio de Fluxo de Caixa para Terminal de Auto-Atendimento

	Novembro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FuncaoConsu 23		//utilizado na Hashing Function da Consulta
#define FuncaoSaque 19		//utilizado na Hashing Function do Saque
#define FuncaoDepos 13		//utilizado na Hashing Function do Deposito
#define FuncaoTrans 17		//utilizado na Hashing Function da Transferencia
#define MaxTable 25			//numero maximo de cada Hashing Table
#define FuncaoTermi 5		//utilizado na Hashing Function dos Terminais

//***********STRUCTS PARA ARMAZENAMENTO**************

typedef struct{

	int bi;		//banco em que foi feito a operacao
	char o;		//operacao
	float v;	//valor da operacao
	int bj;		//banco de destino (em caso da trasferencia)

}operac;

typedef struct{

	operac item[8][MaxTable];	//Hashing Tables
	//3 para as bem sucedidas e 3 para as com erro
	//sendo 3 as operacoes guardadas (Saque, Trasferencia, Deposito)
	int cont[8];				//contador de quantos itens tem em cada Hashing Table

}t_operac;

//**************STRUCTS PARA AUDITORIA***************

//vai armazenando as auditorias requeridas numa fila para depois sair na saida na ordem pedida
typedef struct{

	int t;		//guarda o terminal de que se quer a auditoria
	char op;	//guarda a operacao de que se quer a auditoria
	int quant;	//guarda a quantidade de operacoes que se quer ver na auditoria

}audit;

typedef struct{
	
	audit item[MaxTable];
	int inicio, fim;

}t_fila;

//******************FUNCOES T_FILA*******************

/*Funcao para colocar os itens na fila
Retorno: 
	void
Parametros:
	t_fila* A = uma fila qualquer
	int terminal = terminal da auditoria requerida
	char operacao = operacao requerida pela auditoria
	int quantidade = quantidade de operacoes para auditoria
*/
void insereFila (t_fila* A, int terminal, char operacao, int quantidade){

	(*A).item[(*A).fim].t = terminal;
	(*A).item[(*A).fim].op = operacao;
	(*A).item[(*A).fim].quant = quantidade;
	(*A).fim++; 

	//printf("terminal: %d, operacao: %c, quantidade: %d\n", terminal, operacao, quantidade);

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
	(*A).item[(*A).fim].t = 0;
	(*A).item[(*A).fim].op = '0';
	(*A).item[(*A).fim].quant = 0;
	(*A).fim--;

}

/*Funcao que inicializa a fila 
Retorno:
	void
Parametros:
	t_fila* A = uma fila qualquer
*/
void inicializaFila (t_fila* A){

	for(int cont = 0; cont < MaxTable; cont++){
		(*A).item[cont].t = 0;
		(*A).item[cont].op = '0';
		(*A).item[cont].quant = 0;
	}

	(*A).inicio = 0;
	(*A).fim = 0;

}


//****************FUNCOES T_OPERAC*******************

void Zeracont (t_operac* terminais){

	for(int cont = 0; cont < 4; cont++){
		for (int cont1 = 0; cont1 < 6; cont1++){
			terminais[cont].cont[cont1] = 0;
		}
	}

}

/*Funcao que insere uma operacao numa das tabelas
Retorno:
	void
Parametros:
	int terminal = terminal em que a operacao foi feita
	char op = operaco que foi feita
	int banco = banco em que foi eita a operacao
	float valor = valor da operacao
	int bancod = banco de destino (em caso de trasferencia)
	t_operac* terminais = a Hashing Table dos terminais
	int erro = indica se e' erro ou nao
*/
void insereOperac(int terminal, char op, int banco, float valor, int bancod, t_operac* terminais, int erro){

	int indice;		//indice que resulta da Hashing Function dos Terminais
	int tabela;		//escolhe uma das tabelas
	int indicet;	//indice da tabela
	int aux;		//auxiliar para aumentar o contador da tabela 

	//Hashing Function dos Terminais
	indice = (terminal % FuncaoTermi) - 1;

	if(erro == 1){
		if(op == 'S')
			tabela = 3;
		else if(op == 'T')
			tabela = 6;
		else if(op == 'D')
			tabela = 4;
		else if(op == 'C')
			tabela = 5;
	}
	else{
		if(op == 'S')
			tabela = 0;
		else if(op == 'T')
			tabela = 1;
		else if(op == 'D')
			tabela = 2;
		else if(op == 'C')
			tabela = 7;
	}

	if(tabela == 0 || tabela == 3){
		indicet = (terminais[indice].cont[tabela] % FuncaoSaque);
		aux = terminais[indice].cont[tabela];
		terminais[indice].cont[tabela] = aux + 1;
	}
	else if(tabela == 1 || tabela == 6){
		indicet = (terminais[indice].cont[tabela] % FuncaoTrans);
		aux = terminais[indice].cont[tabela];
		terminais[indice].cont[tabela] = aux + 1;
	}
	else if(tabela == 2 || tabela == 4){
		indicet = (terminais[indice].cont[tabela] % FuncaoDepos);
		aux = terminais[indice].cont[tabela];
		terminais[indice].cont[tabela] = aux + 1;
	}
	else if(tabela == 7 || tabela == 5){
		indicet = (terminais[indice].cont[tabela] % FuncaoConsu);
		aux = terminais[indice].cont[tabela];
		terminais[indice].cont[tabela] = aux + 1;
	}

	//printf("terminal: %d, operacao: %d, lugar: %d, valor: %.2f\n", indice, tabela, indicet, valor);

	terminais[indice].item[tabela][indicet].bi = banco;
	terminais[indice].item[tabela][indicet].o = op;
	terminais[indice].item[tabela][indicet].v = valor;
	terminais[indice].item[tabela][indicet].bj = bancod;

}

/*Funcao que */

//*****************FUNCOES MAIN**********************

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

/*Funcao que zera todos os itens de um vetor de float
Retorno:
	void
Parmaetros
	float* A = um vetor de float qualquer
	int tam = tamano do vetor
*/
void Zeravetor(float* A, int tam){

	for (int cont = 0; cont < tam; cont++){
		A[cont] = 0;
	}

}

//*********************MAIN**************************

int main (){

	int terminal;			//terminal para fazer a operacao
	int banco;				//codigo de identificacao do banco
	char operacao;			//operacao desejada
	float valor;			//valor para operacao
	int destino;			//casos de trasferencia entre bancos distintos
	int numero;				//numero de operacoes (caso auditoria)
	int num = 0;			//numero de operacoes
	int lucro;				//variavel para mostrar o lucro de cada terminal
	int lucrofim;			//variavel que guarda o lucro final
	t_fila audito;			//guarda a auditoria para o problema
	int bancospos[4];		//bancos possiveis 
	int bancos = 0;			//guarda o numero de bancos utilizados dos terminais
	int aux4 = 0;			//auxiliar que ajuda na contabilizacao do lucro;

	t_operac terminais[FuncaoTermi];	//acesso aos terminais

	char auxiliar[10] = {'0'};	//auxiliar para deferenciar a auditoria das outras operacoes
	char auxiliar2[10] = {'0'};	//auxiliar para entrada com mensagem de ERRO

	//todas as variaveis abaixo servem para deixar salvo a entrada anterior
	//caso haja um erro elas sao colocadas em outra Hashing Table especifica
	//sendo 'erro', 'auditoria' e 'aux' variaveis q auxiliam nesse processo
	int terminalA = 0;
	char operacaoA = '0';
	int bancoA = 0;
	float valorA = 0;
	int bancodA = 0;
	int erro = 2;
	int auditoria = 0;
	int aux = 1;

	//inicializa a fila que guarda as auditorias requeridas
	inicializaFila(&audito);
	for(int cont = 0; cont < 4; cont++)
		bancospos[cont] = 0;
	Zeracont(terminais);

	//como o loop so' vai ate' EOF a ultima linha acaba por ficar de fora
	//portanto ha' uma nova insercao depois desse loop
	while(scanf("%s", auxiliar2) != EOF){

		if(auxiliar2[0] == 'E'){
			//deu mensagem de ERRO
			erro = 1;
		}

		//if(erro != 1 && auditoria != 1)
			//lucro[terminalA - 1]++;

		if(num > 0 && auditoria != 1 && aux > 0){
			insereOperac(terminalA, operacaoA, bancoA, valorA, bancodA, terminais, erro);
			if(erro == 1)
				aux = 0;
		}
		else if(num > 0 && auditoria == 1 && aux > 0)
			insereFila(&audito, terminalA, operacaoA, bancoA);

		//serve para alocar os bancos possiveis dos terminais
		if(erro != 1 && operacaoA != 'C' && auditoria != 1){
			int dif = 0;		//indica se tal banco ja esta no vetor 'bancopos'
			for(int cont = 0; cont < 4; cont++){
				if(bancoA != bancospos[cont])
					dif++;
			}
			if(dif == 4){			
				for(int cont = 0; cont < 4; cont++){
					if(bancospos[cont] == 0){
						bancospos[cont] = bancoA;
						bancos++;
						break;
					}
				}
			}
		}
		
		//guarda o terminal
		if (auxiliar2[0] != 'E'){
			terminal = transforma(auxiliar2);
			terminalA = terminal;
			auditoria = 0;
			erro = 0;
			aux++;

			getchar();
			scanf("%s", auxiliar);

			//caso auxiliar for da auditoria
			if(auxiliar[0] == 'S' || auxiliar[0] == 'T' || auxiliar[0] == 'D'){
				auditoria++;
				operacao = auxiliar[0];
				operacaoA = operacao;
				auditoria = 1;

				getchar();
				scanf("%d", &numero);
				bancoA = numero;
				//printf("%d %c %d\n", terminal, operacao, numero);
			}
			//caso auxiliar for o codigo do banco
			else{
				banco = transforma(auxiliar);
				bancoA = banco;

				auditoria = 0;

				getchar();
				scanf("%c", &operacao);
				operacaoA = operacao;

				//operacao de saque
				if(operacao == 'S'){
					getchar();
					scanf("%f", &valor);
					valorA = valor;
					bancodA = 0;
					//printf("%d %d %c %.2f\n", terminal, banco, operacao, valor);
				}
				//operacao de trasferencia
				else if(operacao == 'T'){
					float auxiliar3;		//ajuda para ver se a trasferencia e' entre dois bancos diferentes
					
					getchar();
					scanf("%f", &auxiliar3);
					
					if(getchar() != ' '){
						valor = auxiliar3;
						valorA = valor;
						bancodA = 0;
						//printf("%d %d %c %.2f\n", terminal, banco, operacao, valor);
					}
					else{
						destino = auxiliar3;
						bancodA = destino;

						scanf("%f", &valor);
						valorA = valor;
						//printf("%d %d %c %d %.2f\n", terminal, banco, operacao, destino, valor);
					}
				}
				//operacao de consulta
				else if(operacao == 'C'){
					operacaoA = operacao;
					bancoA = 0;
					bancodA = 0;
					//printf("%d %d %c\n", terminal, banco, operacao);
				}
				//operacao de deposito
				else{
					getchar();
					scanf("%f", &valor);
					valorA = valor;
					//printf("%d %d %c %.2f\n", terminal, banco, operacao, valor);
				}
			}
		}
		num++;
	}
	if(num > 0 && operacaoA != 'C' && auditoria != 1 && aux > 0)
		insereOperac(terminalA, operacaoA, bancoA, valorA, bancodA, terminais, erro);
	else if(num > 0 && operacaoA != 'C' && auditoria == 1 && aux > 0)
		insereFila(&audito, terminalA, operacaoA, bancoA);
	//if(erro != 1 && auditoria != 1)
			//lucro[terminalA - 1]++;

	for(int ini = 0; ini < bancos - 1; ini++){
		for (int fim = 0; fim < bancos - ini - 1; fim++){
			if(bancospos[fim] > bancospos[fim + 1]){
				int troca = bancospos[fim];
				bancospos[fim] = bancospos[fim + 1];
				bancospos[fim + 1] = troca;
			}
		}
	}

	//indice da Hashing Function
	int indice;

	//variaveis para armazenar os estratos do fim do dia
	float fimbanco[4][4];		//para a contabilizacao da moeda e da trasferencia no 'TOTAL'
	float negm[4], posm[4];		//saldo negativo e positivo das moedas
	float negt[4], post[4];		//saldo negativo e positivo das trasferencias
	float aux2;					//ajuda na somatoria dos saldos
	int error[4];				//armazena os erros em cada terminal
	int totalerror[4];			//guarda o numero total de erros

	//parte do codigo para fazer a mostra no fim do dia
	for(int cont = 0; cont < 4; cont++){
		printf("===TERMINAL %d===\n", cont + 1);

		Zeravetor(negm, 4);
		Zeravetor(posm, 4);
		Zeravetor(negt, 4);
		Zeravetor(post, 4);
		
		indice = ((cont + 1) % FuncaoTermi) - 1;
		
		//primeiro procura saque para o saldo negativo da moeda
		//sendo '0' = saque bem sucedido
		for(int cont1 = 0; cont1 < terminais[indice].cont[0]; cont1++){	
			for(int cont2 = 0; cont2 < bancos; cont2++){
				if(bancospos[cont2] == terminais[indice].item[0][cont1].bi){
					aux2 = negm[cont2];
					negm[cont2] = aux2 + terminais[indice].item[0][cont1].v;
				}
			}
		}

		//sendo '1' = trasferencia bem sucedida
		for(int cont1 = 0; cont1 < terminais[indice].cont[1]; cont1++){	
			for(int cont2 = 0; cont2 < bancos; cont2++){
				if(bancospos[cont2] == terminais[indice].item[1][cont1].bi){
					if(terminais[indice].item[1][cont1].bj != 0){
						aux2 = negt[cont2];
						negt[cont2] = aux2 + terminais[indice].item[1][cont1].v;
						int aux3 = 0;
						for(aux3 = 0; aux3 < bancos; aux3++){
							if(bancospos[aux3] == terminais[indice].item[1][cont1].bj)
								break;
						}
						aux2 = post[aux3];
						post[aux3] = aux2 + terminais[indice].item[1][cont1].v;
					}
				}
			}
		}

		//sendo '2' = deposito bem sucedido
		for(int cont1 = 0; cont1 < terminais[indice].cont[2]; cont1++){	
			for(int cont2 = 0; cont2 < bancos; cont2++){
				if(bancospos[cont2] == terminais[indice].item[2][cont1].bi){
					aux2 = posm[cont2];
					posm[cont2] = aux2 + terminais[indice].item[2][cont1].v;
				}
			}
		}

		//sendo '3' '4' '5' '6' = as Hashing Tables que armazenam os possiveis erros das operacoes 
		int aux3 = 0;
		for(int cont1 = 3; cont1 < 7; cont1++){
			error[aux3] = terminais[indice].cont[cont1];
			aux3++;
		}

		//guarda para mostrar o resultado total
		for(int cont1 = 0; cont1 < bancos; cont1++){
			aux2 = fimbanco[cont1][0];
			fimbanco[cont1][0] = negm[cont1]+ aux2;
			aux2 = fimbanco[cont1][1];
			fimbanco[cont1][1] = posm[cont1]+ aux2;
			aux2 = fimbanco[cont1][2];
			fimbanco[cont1][2] = negt[cont1]+ aux2;
			aux2 = fimbanco[cont1][3];
			fimbanco[cont1][3] = post[cont1]+ aux2;
		}

		//guarda para mostrar os erros no fim
		for(int cont1 = 0; cont1 < 4; cont1++){
			aux2 = totalerror[cont1];
			totalerror[cont1] = error[cont1]+ aux2;
		}

		for(int cont1 = 0; cont1 < bancos; cont1++){
			if(negm[cont1] != 0 || posm[cont1] != 0 || negt[cont1] != 0 || post[cont1] != 0){
				printf("Banco %d: Moeda +%.2f -%.2f Transferencia +%.2f -%.2f\n", bancospos[cont1], posm[cont1], negm[cont1], post[cont1], negt[cont1]);
			}
		}

		lucro = 0;
		
		lucro  = terminais[indice].cont[0] + terminais[indice].cont[1] + terminais[indice].cont[2] + terminais[indice].cont[7]; 

		printf("Lucro obtido: %d.00\n", 3 * lucro);

		//printar os erros
		for(int cont1 = 0; cont1 < 4; cont1++){
			if(error[cont1] != 0){
				if(cont1 == 0)
					printf("Erros de saque: %d\n", error[cont1]);
				if(cont1 == 1)
					printf("Erros de deposito: %d\n", error[cont1]);
				if(cont1 == 2)
					printf("Erros de consulta: %d\n", error[cont1]);
				if(cont1 == 3)
					printf("Erros de transferencia: %d\n", error[cont1]);
			}
		}
		aux3 = error[0] + error[1] + error[2] + error[3];
		if(aux3 > 0)
			printf("Total de erros: %d\n", aux3);

	
	}
	//parte do total no fim do dia
	printf("===TOTAL===\n");

	for(int cont = 0; cont < bancos; cont++){
		printf("Banco %d: Moeda +%.2f -%.2f Transferencia +%.2f -%.2f\n", bancospos[cont], fimbanco[cont][1], fimbanco[cont][0], fimbanco[cont][3], fimbanco[cont][2]);
	}

	//busca e calcula o lucro total final
	for(int indice = 0; indice < 4; indice++){
		aux4 = lucrofim;
		lucrofim  = aux4 + terminais[indice].cont[0] + terminais[indice].cont[1] + terminais[indice].cont[2] + terminais[indice].cont[7]; 
	}
	printf("Lucro obtido: %d.00\n", 3 * lucrofim);
	
	//printar os erros
	for(int cont1 = 0; cont1 < 4; cont1++){
		if(totalerror[cont1] != 0){
			if(cont1 == 0)
				printf("Erros de saque: %d\n", totalerror[cont1]);
			if(cont1 == 1)
				printf("Erros de deposito: %d\n", totalerror[cont1]);
			if(cont1 == 2)
				printf("Erros de consulta: %d\n", totalerror[cont1]);
			if(cont1 == 3)
				printf("Erros de transferencia: %d\n", totalerror[cont1]);
		}
	}
	int aux3 = totalerror[0] + totalerror[1] + totalerror[2] + totalerror[3];
	if(aux3 > 0)
		printf("Total de erros: %d\n", aux3);
	
	//parte do codigo para a auditoria caso requerida
	if(audito.fim != audito.inicio){
		printf("===AUDITORIA===\n");
	}
	while(audito.fim != audito.inicio){
		int contador = 1;		//contador para a quantidade de operacoes requeridas da auditoria
		int ajuda = 0;			//ajuda a ver qual e' a Hashing Table certa
		indice = (audito.item[0].t % FuncaoTermi) - 1;
		if(audito.item[0].op == 'S'){
			printf("===SAQUE TERMINAL %d===\n", audito.item[0].t);
			ajuda = 0;
		}
		else if(audito.item[0].op == 'T'){
			printf("===TRANSFERENCIA TERMINAL %d===\n", audito.item[0].t);
			ajuda = 1;
		}
		else if(audito.item[0].op == 'D'){
			printf("===DEPOSITO TERMINAL %d===\n", audito.item[0].t);
			ajuda = 2;
		}
		printf("Mostrando primeiros %d resultados\n", audito.item[0].quant);
		if(terminais[indice].cont[ajuda] == 0)
			printf("Sem resultados\n");
		else{
			if(ajuda == 0 || ajuda == 2){
				for(int cont = 0; cont < terminais[indice].cont[ajuda]; cont++){
					if(cont == audito.item[0].quant)
						break;
					printf("%d- Banco %d %.2f\n", contador, terminais[indice].item[ajuda][cont].bi, terminais[indice].item[ajuda][cont].v);
					contador++;
				}
			}
			else if(ajuda == 1){
				for(int cont = 0; cont < terminais[indice].cont[ajuda]; cont++){
					if(cont == audito.item[0].quant)
						break;
					if(terminais[indice].item[ajuda][cont].bj == 0)
						printf("%d- Banco origem %d Banco destino %d %.2f\n", contador, terminais[indice].item[ajuda][cont].bi, terminais[indice].item[ajuda][cont].bi, terminais[indice].item[ajuda][cont].v);
					else
						printf("%d- Banco origem %d Banco destino %d %.2f\n", contador, terminais[indice].item[ajuda][cont].bi, terminais[indice].item[ajuda][cont].bj, terminais[indice].item[ajuda][cont].v);
					contador++;
				}
			}
		}
		retiraFila(&audito);
	}

	return 0;

}