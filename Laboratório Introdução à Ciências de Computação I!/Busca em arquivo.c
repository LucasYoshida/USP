#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* c;
	int tam;
	int oc;
} word;

unsigned char letraIgual(char l1, char l2){
	if(l1==l2)
		return 1;
	if(l1<l2){
		if(l1 > 64 && l1 == (l2-32))
			return 1;
	}
	else{
		if(l2 > 64 && l2 == (l1-32))
			return 1;
	}
	return 0;
		
}

void buscaPalavra(word *plvr, char* texto, int tamArq){
	
	int cont, cont2;
	plvr->oc = 0;
	for(cont=0; cont<tamArq; cont++){
	
		//entao checa se existe a palavra
		for(cont2=0; cont2<plvr->tam; cont2++){
			if(!letraIgual(texto[cont+cont2], plvr->c[cont2]))
				break;
		}
		if(cont2 == plvr->tam && texto[cont+cont2] < 65 && (texto[cont+cont2] != '-' )){	//achou palavra(em tese)
			if(cont>0 && (texto[cont-1] < 65) && (texto[cont-1] != '-')){
				cont+=plvr->tam-1;
				plvr->oc++;
			}
		}
	}
}

int main () {

	char *nomeArq = (char*)malloc(30 * sizeof(char));	//nome do arquivo
	int n;												//numero de palavras a serem encontradas
	FILE *arq; 											//serve para abrir e fechar o arquivo .txt
	int tam;											//guarda o tamanho do arquivo texto
	char *texto;										//guarda o texto passado
	char temp[30];										//ajuda na ordenacao
	int aux;											//ajuda na ordenacao
	word* palavras;

	//primeira linha da entrada
	scanf("%s %d", nomeArq, &n);

	//abrindo o arquivo
	arq = fopen(nomeArq, "r");

	//alocacao das palavras e pedacos
	palavras = (word*)malloc(n * sizeof(word));

	//entrada das palavras
	for(int cont1 = 0; cont1 < n; cont1++){
		palavras[cont1].c  = (char*)malloc(30);
		scanf("%s", palavras[cont1].c);
		palavras[cont1].tam = strlen(palavras[cont1].c);
		getchar();
	}

	//ordenacao
	for(int i = 1; i < n; i++){
        for (int j = 0; j < n-1; j++){             
            if(strcmp(palavras[j].c , palavras[j+1].c) > 0){
            	strcpy(temp , palavras[j].c);
            	strcpy(palavras[j].c , palavras[j+1].c);
            	strcpy(palavras[j+1].c , temp);
            	aux = palavras[j].tam;
            	palavras[j].tam  = palavras[j+1].tam;
            	palavras[j+1].tam = aux;
            	aux = palavras[j].oc;
            	palavras[j].oc  = palavras[j+1].oc;
            	palavras[j+1].oc = aux;            
           }      
        }
    }

	//ve o tamanho do texto
	fseek(arq, 0, SEEK_END);
	tam = (int)ftell(arq);
	fseek(arq,0,SEEK_SET);

	//alocacao do texto
	texto = (char*)malloc(tam * sizeof(char));

	//leitura do texto e alocacao num vetor
	fread(texto, 1, tam, arq);

	//procura a palavra no texto
 	for (int cont=0; cont < n; cont++){
		buscaPalavra(palavras+cont, texto, tam);
		printf("%s %d\n", palavras[cont].c, palavras[cont].oc);
	}

	//free

	free(texto);

	//fechar o arquivo aberto
	fclose(arq);

	return 0;

}