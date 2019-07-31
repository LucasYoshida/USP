/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Trabalho II - Labirinto

	Setembro - 2017

	Lucas Noriyuki Yoshida - 10262586

***************************************************
*/

#include <stdio.h>
#include <stdlib.h>

//struct que representa as camaras
typedef struct camaras {
	int v;			//indice -> posicao da camara
	int o;			//valor logico -> se tem portal de saida ou nao
} camara;

//struct que representa os segmentos e as acoes
typedef struct segmentos {
	int b;			//indice -> de um dos lados do segmento
	int e;			//indice -> do lado oposto do segmento acima
} segmento;

//struct que representa os pontos
typedef struct pontos {
	float x;		//eixo x
	float y;		//eixo y
} ponto;

//struct que serve para guardar a matriz que ajuda nos possiveis caminhos
typedef struct caminhos {
	int pos;		//guarda quantos portais cada ponto tem
	int** cam;		//matriz que guarda o ponto que pode seguir e se tem saida
} caminho;

//struct que serve para guardar os valores logicos a serem utilizados em cada ponto ao percorrer a matriz
typedef struct valorlogico{
	int bif;		//quantas bifurcacoes cada ponto tem
	int run;		//se o ponto ja foi percorrido
	int sai;		//se o ponto possui saida
} vl;

//**********************************************************************************

/*Funcao que complementa a matriz se pode seguir ou nao com os valores dos pontos
Retorno:
	void
Parametros:
	int NP == numero de pontos
	caminho* aux == auxilia na hora de guardar no vetor de resultado
*/
void comp(int NP, caminho* aux){
	
	for(int cont = 0; cont < NP; cont++){
		for(int cont1 = 0; cont1 < NP; cont1++){
			aux[cont].cam[cont1][0] = cont1 + 1;
		}
	}

}

/*Funcao que modifica o vetor de segmentos conforme as acoes
Retorno:
	void
Parametros:
	int NA == numero de acoes
	segmento* a == vetor que guarda as acoes
	int NS == numero de segmentos
	segmento* s1 == vetor que guarda os segmentos + acoes
*/
void acoes(int NA, segmento* a, int NS, segmento* s1){

	int aux1;		//auxiliador na mudanca
	int aux2;		//auxiliador na verificacao se tem esse caminho ou nao
	int aux3 = 0;	//auxiliador na hora de colocar no vetor

	for(int cont = 0; cont < NA; cont++){
		aux2 = 0;
		for(int cont1 = 0; cont1 < NS; cont1++){
			if(a[cont].b == s1[cont1].b){
				if(a[cont].e == s1[cont1].e * -1){
					aux1 = s1[cont1].e;
					s1[cont1].e = aux1 * -1;
				}
			}
			if(a[cont].e == s1[cont1].b){
				if(a[cont].b == s1[cont1].e * -1){
					aux1 = s1[cont1].e;
					s1[cont1].e = aux1 * -1;	
				}
			}
			if((a[cont].b == s1[cont1].b && a[cont].e == s1[cont1].e) || (a[cont].b == s1[cont1].e && a[cont].e == s1[cont1].b)){
			  aux2 = 0;
			}
			else{
			  aux2++;
			}
		}
		if(aux2 == NS){
	    s1[NS + aux3].b = a[cont].b;
			s1[NS + aux3].e = a[cont].e;
			aux2 = 0;
			aux3++;
		}
	}

}

/*Funcao que encontra qual o numero de portais que cada ponto possui
Retorno:
	void
Parametros:
	caminho* aux == auxilia na hora de guardar no vetor de resultado
	int NP == numero de pontos
*/
void numero (caminho* aux, int NP){

	int aux1 = 0;		//auxilia na contagem de portais

	//quantos portais cada ponto tem
	for(int cont = 0; cont < NP; cont++){
		for(int cont1 = 0; cont1 < NP; cont1++){
			if(aux[cont].cam[cont1][1] == 1){
				aux1 = aux[cont].pos;
				aux[cont].pos = aux1 + 1;
			}
		}
	}

	//tira um caminho pq nao pode voltar
	for(int cont = 0; cont < NP; cont++){
		aux1 = aux[cont].pos;
		aux[cont].pos = aux1 - 1;
	}
	
}

/*Funcao que ajuda para colocar na matriz os caminhos possiveis que a cada ponto pode seguir
Retorno:
	void
Parametros:
	int NS == numero de segmentos
	segmento* s == vetor que guarda os segmentos
	caminho* aux == auxlia na hora de guardar no vetor de resultado
	int NC == numero de camaras
	camara* c == vetor que guarda as camaras
*/
void seguir (int NS, segmento* s, caminho* aux, int NC, camara* c){

	//ver se tem segmento
	for(int cont = 0; cont < NS; cont++){
		if(s[cont].b > 0 && s[cont].e > 0){
			aux[s[cont].b - 1].cam[s[cont].e -1][1] = 1;
			aux[s[cont].e - 1].cam[s[cont].b -1][1] = 1;
		}
	}

	//ver se tem portal de saida
	for(int cont = 0; cont < NC; cont++){
		if(c[cont].o == 1){
			aux[c[cont].v - 1].cam[c[cont].v - 1][1] = 1;
			aux[c[cont].v - 1].pos = 1;
		}
	}

}

/*Funcao que serve para dar valor logico aos pontos e com isso auxiliar no labirinto
Retorno:
	void
Parametros:
	int NC == numero de camaras
	camara* c == vetor que guarda as camaras
	vl* valor == valores que facilitam para percorrer o labirinto
	int NP == numero de pontos
	caminho* aux == auxilia na hora de guardar no vetor de resultado
*/
void valor_logico (int NC, camara* c, vl* valor, int NP, caminho* aux){

	//ver se tem saida
	for(int cont = 0; cont < NC; cont++){
		if(c[cont].o != 0){
			valor[c[cont].v - 1].sai = 1;
		}
		else{
			valor[c[cont].v - 1].sai = 0;
		}
	}

	//ver as bifurcacoes
	for(int cont = 0; cont < NP; cont++){
		valor[cont].bif = aux[cont].pos;
	}

}

/*Funcao que iguala um vetor com outro
Retorno:
	void
Parametros:
	int* resul == vetor da matriz que guarda os resultados encontrados
	int* resul1 == vetor que auxilia no armazenamento do resultado
	int num == numero de caracteres que o vetor possui
*/
void iguala(int* resul, int* resul1, int num){

	for(int cont = 0; cont < num; cont++){
		resul[cont] = resul1[cont] + 1;
	}

}

/*Funcao que acha a bifurcacao (posicao) anterior do ponto de saida ou sem saida
Retorno:
	int cont == se encontra um ponto anterior que possua a bifurcacao
	-1 == se nao encontra um ponto anteriror que possua bifurcacao
Parametros:
	vl* valor == valores que facilitam para percorrer o labirinto
	int aux1 == auxilia na verificacao se o ponto tem bifurcacao ou nao
	int* resul == vetor que guarda o valor parcial da saida
*/
int anterior(vl* valor, int aux1, int* resul){

	for(int cont = aux1; cont >= 0; cont--){
		if(valor[resul[cont]].bif >= 1){
			return cont;
		}
	}

	return -1;

}

/*Funcao que acha o proximo ponto do labirinto que deve seguir
Retorno:
	int cont1 == novo ponto do labirinto
	-1 == caso nao ache o proximo lugar a ir (beco sem saida)
Parametros:
	caminho* aux == auxilia na hora de guardar no vetor de resultado
	int NP == numero de pontos
	int posi == posicao em que esta
*/
int proximo(caminho* aux, int NP, int posi){

	for(int cont1 = 0; cont1 < NP; cont1++){
		if(aux[posi].cam[cont1][1] == 1 && aux[posi].cam[cont1][0] != posi + 1){
			return cont1;
		}
	}

	return -1;

}

/*Funcao que serve para quando nao houver um proximo caminho (beco sem saida) trancar o segmento anterior
Retorno:
	void
Paramentros:
	caminho* aux == auxilia na hora de guardar no vetor de resultado
	int pri == primeiro numero (ponto em que estava)
	int seg == segundo numero (ponto em que esta)
*/
void tranca(caminho* aux, int pri, int seg){

	aux[seg].cam[pri][1] = 0;

}	

/*Funcao que serve para criar os vetores responsaveis de guardar os caminhos do labirinto
Retorno:
	void
Parametros:
  int NP == numero de pontos
  vl* valor == valores que facilitam para percorrer o labirinto
  int** resul == matriz que guarda os resultados encontrados
  int inicio == ponto do inicio do labirinto
  caminho* aux == auxilia na hora de guardar no vetor de resultado
*/
void andar(int NP, vl* valor, int** resul, int inicio, caminho* aux){
  
	int cont = inicio - 1;		//auxilia para percorrer o labirinto
	int aux1 = 1;				//auxilia na contagem
	int aux2 = 2;				//auxilia na contagem
	int aux3 = 0;				//auxilia no caminho
	int aux4 = 0;				//auxilia na contagem
	int* resul1;				//vetor que auxilia no armazenamento do resultado

	resul1 = (int*)calloc(30, sizeof(int));

 	resul[0][0] = cont;
  
	aux1 = valor[cont-1].bif;
	valor[cont].bif = aux1 - 1;
  
	aux[cont].cam[cont][1] = 0;
  
	resul1[0] = cont;
  
  	aux3 = proximo(aux, NP, cont);
  
 	resul1[1] = aux3;
  
 	cont = aux3;

	while(cont >= 0){
  		if(valor[cont].bif >= 1){
  			aux3 = proximo(aux, NP, cont);
  			if(aux3 < 0){
  				aux4 = anterior(valor, aux2, resul1);
  				cont = aux4;
  				aux1 = valor[resul1[aux2]].bif;
  				valor[resul1[aux2]].bif = aux1 - 1;
  				tranca(aux, aux4 + 1, aux4);
  				aux2 = aux4;
  			}
  			else{
  				aux3 = proximo(aux, NP, resul1[aux2]);
  				cont = aux3;
  				resul1[aux2] = aux3;
  				tranca(aux, aux4 + 1, aux4);
  				if(valor[cont].sai == 1){
  					iguala(resul[aux1], resul1, aux2);
  					aux1++;
  					aux4 = anterior(valor, aux2, resul1);
  					cont = aux4;
  					aux1 = valor[resul1[aux2]].bif;
  					valor[resul1[aux2]].bif = aux1 - 1;
  					tranca(aux, aux4 + 1, aux4);
  					for(int cont1 = 0; cont1 < aux2; cont1++){
	 					printf("%d ", resul1[cont1]+1);
					}
					printf("\n");
  					aux2 = aux3;
  					aux2++;
  				}
  			}
  		}
  		else{
  			break;
  		}
  	}

  free(resul1);

} 


//**********************************************************************************

int main () {

	//variaveis
	ponto* p;			//vetor que guardar os pontos 
	camara* c;			//vetor que guarda as camaras
	segmento* s;		//vetor que guarda os segmentos
	segmento* a;		//vetor que guarda as acoes
	segmento* s1;		//vetor que guarda os segmentos + acoes
	int NP;				//numero de pontos
	int NC;				//nuemro de camaras
	int NS;				//numero de segmentos
	int NA;				//numero de acoes
	int tesouro;		//ponto onde esta o tesouro
	int preco;			//valor do tesouro
	int inicio;			//ponto do inicio do labirinto
	caminho* aux;		//auxilia na hora de guardar no vetor de resultado
	caminho* auxiliar;	//auxilia quando as acoes forem efetivadas
	vl* valor;			//valores que facilitam para percorrer o labirinto
	vl* valor1;			//valores que facilitam para percorrer o labirinto modificado pelas acoes
	int** resul;		//vetor que guarda os resultados possiveis do labirinto	

	//entrada do numero de pontos
	scanf("%d", &NP);
	
	//malloc dos pontos
	p = (ponto*)calloc(NP, sizeof(ponto));
	//entrada dos pontos
	for(int cont = 0; cont < NP; cont++){
		scanf("%f %f", &p[cont].x, &p[cont].y);
	}

	//entrada do numero de camaras
	scanf("%d", &NC);
	//malloc das camaras
	c = (camara*)calloc(NC, sizeof(camara));
	//entrada das camaras
	for(int cont = 0; cont < NC; cont++){
		scanf("%d %d", &c[cont].v, &c[cont].o);
	}
	
	//entrada do numero de segmentos
	scanf("%d", &NS);

	//malloc dos segmentos
	s = (segmento*)calloc(NS, sizeof(segmento));
	//entrada dos segmentos
	for(int cont = 0; cont < NS; cont++){
		scanf("%d %d", &s[cont].b, &s[cont].e);
	}

	//malloc dos segmentos + acoes
	s1 = (segmento*)calloc(NS + NA + 1, sizeof(segmento));
	//guarda s em s1
	for(int cont = 0; cont < NS; cont++){
		s1[cont] = s[cont];
	}

	//malloc dos valores de cada ponto
	valor = (vl*)calloc(NP, sizeof(vl));

	//malloc dos valores de cada ponto do labirinto modificado
	valor1 = (vl*)calloc(NP, sizeof(vl));

	//entrada do tesouro(DLC)
	scanf("%d %d", &tesouro, &preco);

	//entrada do numero de acoes
	scanf("%d", &NA);

	//malloc das acoes
	a = (segmento*)calloc(NA, sizeof(segmento));
	//entrada das acoes
	for(int cont = 0; cont < NA; cont++){
		scanf("%d %d", &a[cont].b, &a[cont].e);
	}

	//entrada do inicio do labirinto
	scanf("%d", &inicio);

	//malloc do auxiliador
	aux = (caminho*)calloc(NP, sizeof(caminho));
	for(int cont = 0; cont < NP; cont++){
  		aux[cont].cam = (int**)calloc(NP, sizeof(int*));
  		for(int cont1 = 0; cont1 < NP; cont1++){
		  aux[cont].cam[cont1] = (int*)calloc(2, sizeof(int));
		}
	}
	auxiliar = (caminho*)calloc(NP, sizeof(caminho));
	for(int cont = 0; cont < NP; cont++){
  		auxiliar[cont].cam = (int**)calloc(NP, sizeof(int*));
  		for(int cont1 = 0; cont1 < NP; cont1++){
		  auxiliar[cont].cam[cont1] = (int*)calloc(2, sizeof(int));
		}
	}

	//malloc da matriz que guarda os resultados
	resul = (int**)calloc(15, sizeof(int*));
	for(int cont = 0; cont < 15; cont++){
		resul[cont] = (int*)calloc(30, sizeof(int));
	}

	acoes(NA, a, NS, s1);

	comp(NP, aux);
	comp(NP, auxiliar);
	
	seguir(NS, s, aux, NC, c);
	seguir(NS + NA, s1, auxiliar, NC, c);

	numero(aux, NP);
	numero(auxiliar, NP);

	valor_logico(NC, c, valor, NP, aux);
	valor_logico(NC, c, valor1, NP, auxiliar);

	andar(NP, valor, resul, inicio, aux);

	//frees
	free(p);
	free(c);
	free(s);
	free(s1);
	free(valor);
	free(valor1);
	free(a);
	for(int cont = 0; cont < NP; cont++){
  		for(int cont1 = 0; cont1 < NP; cont1++){
		  free(aux[cont].cam[cont1]);
	  	}
  		free(aux[cont].cam);
  	}
	free(aux);
	for(int cont = 0; cont < NP; cont++){
  		for(int cont1 = 0; cont1 < NP; cont1++){
		  free(auxiliar[cont].cam[cont1]);
	  	}
  		free(auxiliar[cont].cam);
  	}
	free(auxiliar);
	for(int cont = 0; cont < 15; cont++){
		free(resul[cont]);
	}
	free(resul);

	return 0;

}