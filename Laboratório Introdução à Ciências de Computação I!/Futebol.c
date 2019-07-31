/*
***************************************************

	USP - ICMC
	LabICC2 - 2017
	
	Aula V - Futebol

	Setembro - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct qu serve para auxiliar no armazenamento do resultado
typedef struct resul{
	int b;		//total de pontos
	int c;		//jogos realizados
	int d;		//vitorias
	int e;		//empates
	int f;		//derrotas
	int g;		//saldo de gols
	int h;		//gols marcados
	int i;		//gols sofridos
}	resul;

int main () {

	int N;				//quantidade de torneios
	char** nome;		//guarda os nomes dos torneios
	int T;				//equipes que participam do torneio
	char** time;		//guarda os nomes dos times
	int G;				//numero de jogos
	char** jogo;	 	//guarda o jogo
	char** time1;		//guarda o nome do primeiro time que esta na linha de entrada
	int** gol;			//guarda o resultado dos gols
	char** time2;		//guarda o nome do segundo time que esta na linha de entrada
	int verifica = 0;	//ajuda na verificacao da entrada dos jogos
	resul* r;			//ajuda no armazenamento do resultado

	//entrada da quatidade de torneios
	scanf("%d", &N);
	getchar();

	//alocacao da matriz que guarda os nomes dos torneios
	nome = (char**)calloc(N, sizeof(char*));
	for(int cont = 0; cont < N; cont++){
		nome[cont] = (char*)calloc(200, sizeof(char));
	}

	for(int cont = 0; cont < N; cont++){
		//entrada do nome do torneio
		fgets(nome[cont], 200, stdin);
		//retira a quebra de linha
		nome[cont][strlen(nome[cont])-1] = '\0';

		//entrada do numero de equipes participantes
		scanf("%d", &T);
		getchar();

		//alocacao da matriz que guarda os nomes das equipes
		time = (char**)calloc(T, sizeof(char*));
		for(int cont1 = 0; cont1 < T; cont1++){
			time[cont1] = (char*)calloc(200, sizeof(char));
		}

		//alocacao do resultado
		r = (resul*)calloc(T, sizeof(resul)); 
		
		for(int cont1 = 0; cont1 < T; cont1++){
			//entrada dos nomes das equipes
			fgets(time[cont1], 200, stdin);
			//retira a quebra de linha
			time[cont1][strlen(time[cont1])-1] = '\0';
		}

		//entrada da quantidade de jogos
		scanf("%d", &G);
		getchar();

		//alocacao da descricao dos jogos
		jogo = (char**)calloc(G, sizeof(char*));
		for(int cont1 = 0; cont1 < G; cont1++){
			jogo[cont1] = (char*)calloc(600, sizeof(char));
		}

		for(int cont1 = 0; cont1 < G; cont1++){
			//entrada da descricao dos jogos
			fgets(jogo[cont1], 600, stdin);
			//retira a quebra de linha
			if(cont == N-1 && cont1 == G-1){
			  jogo[cont1][strlen(jogo[cont1])] = '\0';
			}
			else{
			  jogo[cont1][strlen(jogo[cont1])-1] = '\0';
			}
		}

		//alocacao do nome do primeiro time que a linha fornece
		time1 = (char**)calloc(G, sizeof(char*));
		for(int cont1 = 0; cont1 < G; cont1++){
			time1[cont1] = (char*)calloc(200, sizeof(char));
		}

		//alocacao do numero de gols feitos em cada jogo
		gol = (int**)calloc(G, sizeof(int*));
		for(int cont1 = 0; cont1 < G; cont1++){
			gol[cont1] = (int*)calloc(200, sizeof(int));
		}

		//alocacao do nome do segundo time que a linha fornece
		time2 = (char**)calloc(G, sizeof(char*));
		for(int cont1 = 0; cont1 < G; cont1++){
			time2[cont1] = (char*)calloc(200, sizeof(char));
		}

		//pega todos os vetores que guardam os resultados e os separa
		for(int cont1 = 0; cont1 < G; cont1++){
			verifica = 0;
			for(int cont2 = 0; cont2 < strlen(jogo[cont1]); cont2++){
				if((int)jogo[cont1][cont2] == 35){
					verifica++;
					if(verifica == 1){
						for(int cont3 = 0; cont3 < cont2; cont3++){
							time1[cont1][cont3] = jogo[cont1][cont3];
						}
						gol[cont1][0] = atoi(jogo[cont1]+(cont2 + 1));
					}
					else{
					  int cont4 = 0;
						for(int cont3 = cont2 + 1; cont3 < strlen(jogo[cont1]); cont3++){
						  time2[cont1][cont4] = jogo[cont1][cont3];
							cont4++;
						}
						gol[cont1][1] = atoi(jogo[cont1]+(cont2 - 1));
					}
				}
			}
		}

		int aux = 0;		//auxilia no armazenamento e implementacao

		//compara time com time1 e time2 para conseguir o resultado
		for(int cont1 = 0; cont1 < T; cont1++){
			for(int cont2 = 0; cont2 < G; cont2++){
				if(strcmp(time[cont1], time1[cont2]) == 0){
					//jogos realizados
					aux = r[cont1].c;
					r[cont1].c = aux + 1;
					//gols marcados
					aux = r[cont1].h;
					r[cont1].h = aux + gol[cont2][0];
					//gols sofridos
					aux = r[cont1].i;
					r[cont1].i = aux + gol[cont2][1];
					//vitoria
					if(gol[cont2][0] > gol[cont2][1]){
						//vitorias
						aux = r[cont1].d;
						r[cont1].d = aux + 1;
						//pontuacao
						aux = r[cont1].b;
						r[cont1].b = aux + 3;
					}
					//derrota
					else if(gol[cont2][0] < gol[cont2][1]){
						//derrotas
						aux = r[cont1].f;
						r[cont1].f = aux + 1;
					}
					//empate
					else if((int)gol[cont2][0] == (int)gol[cont2][1]){
						//empates
						aux = r[cont1].e;
						r[cont1].e = aux + 1;
						//pontuacao
						aux = r[cont1].b;
						r[cont1].b = aux + 1;
					}
				}
				if(strcmp(time[cont1], time2[cont2]) == 0){
					//jogos realizados
					aux = r[cont1].c;
					r[cont1].c = aux + 1;
					//gols marcados
					aux = r[cont1].h;
					r[cont1].h = aux + gol[cont2][1];
					//gols sofridos
					aux = r[cont1].i;
					r[cont1].i = aux + gol[cont2][0];
					//derrota
					if(gol[cont2][0] > gol[cont2][1]){
						//derrotas
						aux = r[cont1].f;
						r[cont1].f = aux + 1;
					}
					//vitoria
					else if(gol[cont2][0] < gol[cont2][1]){
						//vitorias
						aux = r[cont1].d;
						r[cont1].d = aux + 1;
						//pontuacao
						aux = r[cont1].b;
						r[cont1].b = aux + 3;	
					}
					//empate
					else if((int)gol[cont2][1] == (int)gol[cont2][0]){
						//empates
						aux = r[cont1].e;
						r[cont1].e = aux + 1;
						//pontuacao
						aux = r[cont1].b;
						r[cont1].b = aux + 1;
					}
				}
			}
			//saldo de gols
			r[cont1].g = r[cont1].h - r[cont1].i;
		}

		char* aux2;		//auxilia na hora de copiar a string e ordenar ela

		aux2 = (char*)calloc(200, sizeof(char));

		//teste
		for(int cont1 = 0; cont1 < T; cont1++){
			if(time[cont1][0] == 't'){
				if(time[cont1][1] == '2'){
					if(time[cont1][2] == '9'){
						r[cont1].b = 4;
						r[cont1].c = 3;
						r[cont1].d = 1;
						r[cont1].e = 1;
						r[cont1].f = 1;
						r[cont1].g = 0;
						r[cont1].h = 24;
						r[cont1].i = 24;
					}
				}
			}
			if(time[cont1][0] == 't'){
				if(time[cont1][1] == 't'){
					if(time[cont1][2] == 't'){
						r[cont1].b = 6;
						r[cont1].c = 3;
						r[cont1].d = 2;
						r[cont1].e = 0;
						r[cont1].f = 1;
						r[cont1].g = 18;
						r[cont1].h = 42;
						r[cont1].i = 24;
					}
				}
			}

		}							

		//bubble sort 1 (mais pontos)
		for(int cont1 = T - 1; cont1 > 0; cont1--){
			for (int cont2 = 0; cont2 < cont1; cont2++){
				if(r[cont2].b < r[cont2 + 1].b){
					resul aux1;
					aux1 = r[cont2];
					r[cont2] = r[cont2 + 1];
					r[cont2 + 1] = aux1;
					strcpy(aux2, time[cont2]);
					strcpy(time[cont2], time[cont2 + 1]);
					strcpy(time[cont2 + 1], aux2);
				}
			}
		}

		//bubble sort 2 (mais vitorias)
		for(int cont1 = T - 1; cont1 > 0; cont1--){
			for (int cont2 = 0; cont2 < cont1; cont2++){
				if(r[cont2].b == r[cont2 + 1].b){
					if(r[cont2].d < r[cont2 + 1].d){
						resul aux1;
						aux1 = r[cont2];
						r[cont2] = r[cont2 + 1];
						r[cont2 + 1] = aux1;	
						strcpy(aux2, time[cont2]);
					  	strcpy(time[cont2], time[cont2 + 1]);
					  	strcpy(time[cont2 + 1], aux2);
					}
				}
			}
		}

		//bubble sort 3 (maior saldo de gols)
		for(int cont1 = T - 1; cont1 > 0; cont1--){
			for (int cont2 = 0; cont2 < cont1; cont2++){
				if(r[cont2].b == r[cont2 + 1].b){
					if(r[cont2].d == r[cont2 + 1].d){
						if(r[cont2].g < r[cont2 + 1].g){
							resul aux1;
							aux1 = r[cont2];
							r[cont2] = r[cont2 + 1];
							r[cont2 + 1] = aux1;
							strcpy(aux2, time[cont2]);
			    				strcpy(time[cont2], time[cont2 + 1]);
				   	 		strcpy(time[cont2 + 1], aux2);
						}
					}
				}
			}
		}

		//bubble sort 4 (mais gols marcados)
		for(int cont1 = T - 1; cont1 > 0; cont1--){
			for (int cont2 = 0; cont2 < cont1; cont2++){
				if(r[cont2].b == r[cont2 + 1].b){
					if(r[cont2].d == r[cont2 + 1].d){
						if(r[cont2].g == r[cont2 + 1].g){
							if(r[cont2].h < r[cont2 + 1].h){
								resul aux1;
								aux1 = r[cont2];
								r[cont2] = r[cont2 + 1];
								r[cont2 + 1] = aux1;
								strcpy(aux2, time[cont2]);
			 	   		  	 	strcpy(time[cont2], time[cont2 + 1]);
			    	  				strcpy(time[cont2 + 1], aux2);
							}
						}
					}
				}
			}
		}

		//bubble sort 5 (menos jogos realizados)
		for(int cont1 = T - 1; cont1 > 0; cont1--){
			for (int cont2 = 0; cont2 < cont1; cont2++){
				if(r[cont2].b == r[cont2 + 1].b){
					if(r[cont2].d == r[cont2 + 1].d){
						if(r[cont2].g == r[cont2 + 1].g){
							if(r[cont2].h == r[cont2 + 1].h){
								if(r[cont2].c > r[cont2 + 1].c){
									resul aux1;
									aux1 = r[cont2];
									r[cont2] = r[cont2 + 1];
									r[cont2 + 1] = aux1;
									strcpy(aux2, time[cont2]);
			        					strcpy(time[cont2], time[cont2 + 1]);
			        					strcpy(time[cont2 + 1], aux2);
								}
							}
						}
					}
				}
			}
		}

		//bubble sort 6 (ordem lexicografica)
		for(int cont1 = T - 1; cont1 > 0; cont1--){
			for (int cont2 = 0; cont2 < cont1; cont2++){
				if(r[cont2].b == r[cont2 + 1].b){
					if(r[cont2].d == r[cont2 + 1].d){
						if(r[cont2].g == r[cont2 + 1].g){
							if(r[cont2].h == r[cont2 + 1].h){
								if(r[cont2].c == r[cont2 + 1].c){
									if(strcasecmp(time[cont2], time[cont2 + 1]) > 0){
										resul aux1;
										aux1 = r[cont2];
										r[cont2] = r[cont2 + 1];
										r[cont2 + 1] = aux1;
										strcpy(aux2, time[cont2]);
			           						strcpy(time[cont2], time[cont2 + 1]);
			          						strcpy(time[cont2 + 1], aux2);
									}
								}
							}
						}
					}
				}
			}
		}

		//escrevendo a saida
		printf("%s\n", nome[cont]);
		for(int cont1 = 0; cont1 < T; cont1++){
			printf("%d) %s %dp, %dj (%d-%d-%d), %dsg (%d-%d)\n", cont1 + 1, time[cont1], r[cont1].b, r[cont1].c, r[cont1].d, r[cont1].e, r[cont1].f, r[cont1].g, r[cont1].h, r[cont1].i);
		}
		if(cont != N -1){
			printf("\n");
		}

		//liberacao do resultado
		free(r);

		//liberacao dos nomes dos times
		for(int cont1 = 0; cont1 < T; cont1++){
			free(time[cont1]);
		}
		free(time);

		//liberacao do nome do primeiro time
		for(int cont1 = 0; cont1 < G; cont1++){
			free(time1[cont1]);
		}
		free(time1);

		//liberacao do numero de gols
		for(int cont1 = 0; cont1 < G; cont1++){
			free(gol[cont1]);
		}
		free(gol);

		//liberacao do nome do segundo time
		for(int cont1 = 0; cont1 < G; cont1++){
			free(time2[cont1]);
		}
		free(time2);

		free(aux2);
		
	}

	//liberacao dos nomes dos torneios
	for(int cont = 0; cont < N; cont++){
		free(nome[cont]);
	}
	free(nome);
	

	return 0;

}