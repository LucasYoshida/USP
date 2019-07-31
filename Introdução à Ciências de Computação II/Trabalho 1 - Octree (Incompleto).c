/*
***************************************************

	USP - ICMC
	ICC2 - 2017
	
	Trabalho I - Octree

	Agosto - 2017

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct arvore TREE;

//struct para representar a arvore referente a caixa delimitadora e suas respectivas octantes
struct arvore {

	//eixos que representam os pontos da caixsa delimitadora
	double xr[8];										
	double yr[8];
	double zr[8];
	//eixos que representam os pontos de maximo e minimo pra criar a caixa e as octantes
	double exX[2];
	double exY[2];
	double exZ[2];
	//eixos para representar o meio da caixa/octante
	double meX;
	double meY;
	double meZ;
	//vetor para as octantes subsequentes
	TREE **octante;

};

//struct para simplificar a usabilidade das variaveis referentes ao objeto colisor e ao ponto medio do triangulo
typedef struct colisor {
	
	//eixos que representam o objeto colisor
	double xp;
	double yp;
	double zp;

} PONTO;

/*
Funcao para ver se há colisão ou não utilizando o metodo de verificar se os pontos medios das arestas dos triangulos estao dentro do octante
Retorno:
	int -> 0 ou 1 == se colide ou nao
Parametros:
	TREE *caixa == struct que representa a caixa delimitadora
	PONTO *medio == representam a mediana das arestas dos triangulos
	int tri == quantidade de triangulos fornecidos
	int cont == mostra em qual nivel da arvore esta
	int oc == mostra qual eh a combinacao da octante verificada
*/
int colide (TREE *caixa, PONTO **medio, int tri, int cont, int oc) {
  
	for(int cont1 = 0; cont1 < tri; cont1++){
		for(int cont2 = 0; cont2 < 3; cont2++){
			if (medio[cont1][cont2].xp >= caixa->octante[cont][oc].exX[1] && medio[cont1][cont2].xp <= caixa->octante[cont][oc].exX[0]){
				if (medio[cont1][cont2].yp >= caixa->octante[cont][oc].exY[1] && medio[cont1][cont2].yp <= caixa->octante[cont][oc].exY[0]){
					if (medio[cont1][cont2].zp >= caixa->octante[cont][oc].exZ[1] && medio[cont1][cont2].zp <= caixa->octante[cont][oc].exZ[0]){
					  return 1;
					}
				}
			}
		}
	}

	return 0;

}

/*
Funcao que verifica se ha colisao tendo como ponto de vista os vertices dos triangulos dos casos
Retorno:
	int -> 0 ou 1 == se colide ou nao
Parametros:
	TREE *caixa == struct referente a caixa delimitadora
	PONTO *t == os pontos dos triangulos fornecidos nos casos
	int tri == quantidade de tringulos fornecidos
	int cont == contador que representa em qual nivel da arvore esta
	int oc == representa a combinacao de octantes 
*/
int colide1 (TREE *caixa, PONTO *t, int tri, int cont, int oc) {

	for(int cont1 = 0; cont1 < tri * 3; cont1++){
	  	if (t[cont1].xp >= caixa->octante[cont][oc].exX[1] && t[cont1].xp <= caixa->octante[cont][oc].exX[0]){
			if (t[cont1].yp >= caixa->octante[cont][oc].exY[1] && t[cont1].yp <= caixa->octante[cont][oc].exY[0]){
				if (t[cont1].zp >= caixa->octante[cont][oc].exZ[1] && t[cont1].zp <= caixa->octante[cont][oc].exZ[0]){
					return 1;
				}
			}
		}
	}

	return 0;

}

/*
Funcao que serve para verificar se o ponto colisor está ou não dentro da caixa delimitadora
Retorno:
	void
Parametros:
	PONTO p == struct refente ao ponto colisor
	TREE *caixa == struct referente a caixa delimitadora
	int cont == contador para guardar o nivel alcancado
	int oc == mostrar em qual octante esta se referindo
*/
int verificar (PONTO p, TREE *caixa, int cont, int oc) {

	if (p.xp >= caixa->octante[cont][oc].exX[1] && p.xp <= caixa->octante[cont][oc].exX[0]){
		if (p.yp >= caixa->octante[cont][oc].exY[1] && p.yp <= caixa->octante[cont][oc].exY[0]){
			if (p.zp >= caixa->octante[cont][oc].exZ[1] && p.zp <= caixa->octante[cont][oc].exZ[0]){
				return 1;
			}
		}
	}

	return 0;

}

/*
Funcao para criar uma octante subsequente
Retorno:
	int -> 0 ou 1 == se colide ou nao
Parametros:
	TREE *caixa == A struct refenete a caixa delimitadora
	int cont == contador para guardar o nivel alcancado
	int *guarda == guarda a octante escolhida
	PONTO p == representa o ponto colisor
	PONTO **medio == representa os pontos que sao medianas das arestas
	int tri == mostra a quantidade de triangulos fornecidos 
	PONTO *t == guarda todos os pontos dos tirangulos fornecidos pelos casos
*/
int octantes (TREE *caixa, int cont, int *guarda, PONTO p, PONTO** medio, int tri, PONTO*t) {

	int resul = 0; 			//guarda o resultado da verificacao se o ponto colisor esta na octante
	int resul1 = 0;			//guarda o resultado da verificacao se ha um ponto medio na octante
	int resul2 = 0;			//guarda o resultado da verificacao se ha um vertice na octante
	int oc = 1;				//serve para ver sobre qual combinacao esta se referindo

	//encontar o meio de cada eixo tendo como base seus extremos
	caixa->octante[cont][0].meX = (caixa->octante[cont-1][*guarda].exX[1] + caixa->octante[cont-1][*guarda].exX[0])/2.0;
	caixa->octante[cont][0].meY = (caixa->octante[cont-1][*guarda].exY[1] + caixa->octante[cont-1][*guarda].exY[0])/2.0;
	caixa->octante[cont][0].meZ = (caixa->octante[cont-1][*guarda].exZ[1] + caixa->octante[cont-1][*guarda].exZ[0])/2.0;

	//combinacoes para cada octante e eh verificado se os os vertices e medianas dos triangulos estao nas mesmas
	//1
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont-1][*guarda].exX[0];
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont-1][*guarda].exY[0];
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont-1][*guarda].exZ[0];
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont][0].meZ;
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 = colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//2
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont-1][*guarda].exX[1];
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont-1][*guarda].exY[0];
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont][0].meZ;
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont-1][*guarda].exZ[1];
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 =colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//3
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont-1][*guarda].exX[1];
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont-1][*guarda].exY[1];
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont-1][*guarda].exZ[1];
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 = colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//4
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont-1][*guarda].exX[0];
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont-1][*guarda].exY[1];
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont][0].meZ;
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont-1][*guarda].exZ[1];
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 =colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//5
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont-1][*guarda].exX[1];
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont-1][*guarda].exY[1];
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont-1][*guarda].exZ[0];
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont][0].meZ;
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 =colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//6
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont-1][*guarda].exX[1];
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont-1][*guarda].exY[0];
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont-1][*guarda].exZ[0];
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont][0].meZ;
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 = colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//7
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont-1][*guarda].exX[0];
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont-1][*guarda].exY[1];
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont-1][*guarda].exZ[0];
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont][0].meZ;
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 = colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}
	oc++;

	//8
	caixa->octante[cont][oc].exX[0] = caixa->octante[cont-1][*guarda].exX[0];
	caixa->octante[cont][oc].exX[1] = caixa->octante[cont][0].meX;
	caixa->octante[cont][oc].exY[0] = caixa->octante[cont-1][*guarda].exY[0];
	caixa->octante[cont][oc].exY[1] = caixa->octante[cont][0].meY;
	caixa->octante[cont][oc].exZ[0] = caixa->octante[cont][0].meZ;
	caixa->octante[cont][oc].exZ[1] = caixa->octante[cont-1][*guarda].exZ[1];
	resul = verificar(p, caixa, cont, oc);
	if(resul == 1){
		*guarda = oc;
		resul1 = colide(caixa, medio, tri, cont, oc);
		resul2 = colide1(caixa, t, tri, cont, oc);
		if(resul1 || resul2){
			return 1;
		}
	}

	return 0;
	
}

//******************************************************************************************************

int main () {

	char n;											//se o caso fornece caixa delimitadora ou não
	int nivel;										//nivel que ate a octree chega
	int tri;										//quantidade de triangulos do objeto alvo
	PONTO p;										//ponto do objeto colisor
	PONTO *t;										//pontos que formam o triangulo
	PONTO **medio;									//acha os pontos medios de cada triangulo do problema
	int cont = 0;									//serve para guardar em que nivel da arvore esta o processo
	int guarda = 0;									//guarda em qual octante se refere
	int oc = 0;										//serve para guardar em qual octante esta
	int resul = 0;									//serve para mostrar qual a resposta desejada
	TREE *caixa = (TREE*)malloc(sizeof(TREE));		//caixa delimitadora inicial 
	
	//entradas
	scanf("%c", &n);

	scanf("%d", &nivel);

	scanf("%d", &tri);

	scanf("%lf %lf %lf", &p.xp, &p.yp, &p.zp);

	//alocacao
	t = (PONTO*)malloc(3 * tri * sizeof(PONTO));

	medio = (PONTO**)malloc(tri * sizeof(PONTO*));
	for(int cont1 = 0; cont1 < tri; cont1++){
		medio[cont1] = (PONTO*)malloc(3 * sizeof(PONTO));
	}

	caixa->octante = (TREE**)malloc(nivel * 3 * sizeof(TREE*));
	for(int cont5 = 0; cont5 < nivel * 3; cont5++){
		caixa->octante[cont5] = (TREE*)malloc(8 * sizeof(TREE));
	}

	//entrada dos triangulos e calculo dos pontos medios que vao auxiliar para verificar se colide ou nao
	for(int cont1 = 0; cont1 < 3 * tri; cont1++){
		scanf("%lf %lf %lf", &t[cont1].xp, &t[cont1].yp, &t[cont1].zp);
	}

	int aux = 0; 		//auxilia no calculo das medianas(pontos medios das arestas dos triangulos)

	//calculo dos pontos medios dos triangulos
	for (int cont1 = 0; cont1 < tri; cont1++){
		
		medio[cont1][0].xp = (t[aux].xp + t[aux+1].xp)/2.0; 
		medio[cont1][1].xp = (t[aux].xp + t[aux+2].xp)/2.0;
		medio[cont1][2].xp = (t[aux+1].xp + t[aux+2].xp)/2.0;
		
		medio[cont1][0].yp = (t[aux].yp + t[aux+1].yp)/2.0;
		medio[cont1][1].yp = (t[aux].yp + t[aux+2].yp)/2.0;
		medio[cont1][2].yp = (t[aux+1].yp + t[aux+2].yp)/2.0;
		
		medio[cont1][0].zp = (t[aux].zp + t[aux+1].zp)/2.0;
		medio[cont1][1].zp = (t[aux].zp + t[aux+2].zp)/2.0;
		medio[cont1][2].zp = (t[aux+1].zp + t[aux+2].zp)/2.0;

		aux += 3;
	}
	
	/*Verifica se tem caixa fornecida ou não
	Se tem (n == '0') já guarda a caixa pela propria entrada e em seguida ve quais sao os maiore e menores valores dos eixos
	Se não (n == '1') vê quais são os maiores e menores valores de x, y e z criando a caixa delimitadora
	*/
	//Se tem caixa ou nao
	if (n == '0'){
		//aloca os pontos da caixa fornecida
		for(int cont2 = 0; cont2 < 8; cont2++){
			scanf("%lf %lf %lf", &caixa->octante[0][0].xr[cont2], &caixa->octante[0][0].yr[cont2], &caixa->octante[0][0].zr[cont2]);
		}
	}

	//Acha os valores dos eixos de maximo e minimo 
	double maior = t[0].xp;		//variavel para auxiliar na descoberta do menor valor dos eixos
	double menor = t[0].xp;		//variavel para auxiliar na descoberta do maior valor dos eixos
	for (int cont3 = 0; cont3 < 3*tri; cont3++){
		if (maior <= t[cont3].xp){
			maior = t[cont3].xp;
		}
		if (menor >= t[cont3].xp){
			menor = t[cont3].xp;
		}
	}
	caixa->octante[0][0].exX[0] = maior;	
	caixa->octante[0][0].exX[1] = menor;
	maior = t[0].yp;
	menor = t[0].yp;
	for (int cont3 = 0; cont3 < 3*tri; cont3++){
		if (maior <= t[cont3].yp){
			maior = t[cont3].yp;
		}
		if (menor >= t[cont3].yp){
			menor = t[cont3].yp;
		}
	}
	caixa->octante[0][0].exY[0] = maior;
	caixa->octante[0][0].exY[1] = menor;
	
	maior = t[0].zp;
	menor = t[0].zp;
	for (int cont3 = 0; cont3 < 3*tri; cont3++){
		if (maior <= t[cont3].zp){
			maior = t[cont3].zp;
		}
		if (menor >= t[cont3].zp){
			menor = t[cont3].zp;
		}
	}
	caixa->octante[0][0].exZ[0] = maior;
	caixa->octante[0][0].exZ[1] = menor;

	//verifica se o ponto colisor está ou não dentro da caixa delimitante
	resul = verificar(p, caixa, cont, oc);

	//'se não esta' == 0
	if(resul == 0){
		printf("0\n");
	}
  
  	//'se esta' == 1 -> verifica as octantes subsequentes 
	else {
		//verifica as octantes ate o ultimo nivel proposto e retorna o resultado consequente
		for (int cont4 = 0; cont4 < nivel; cont4++){
		  cont++;
		  resul = octantes(caixa, cont, &guarda, p, medio, tri, t);
		} 
		printf("%d\n", resul);
	}

	//free
	free (t);

	for(int cont5 = 0; cont5 < nivel * 3; cont5++){
		free(caixa->octante[cont5]);
	}
	free(caixa->octante);

	for(int cont1 = 0; cont1 < tri; cont1++){
		free(medio[cont1]);
	}
	free(medio);

	free (caixa);

	return 0;

}