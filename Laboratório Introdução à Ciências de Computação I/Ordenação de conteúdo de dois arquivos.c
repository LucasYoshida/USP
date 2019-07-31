#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct CPF{

   char num[100];
   char nome[100];
   int idade;

}CPF;

void ordena (CPF* doc, int c) {

	int i, j;
   CPF aux;

   for (i = 0; i < c+1; i++){
   	if(strcmp(doc[c].num, doc[i].num) < 0){
			aux = doc[i];
			doc[i] = doc[c];
			for (j = c; j > i+1; j--)
				doc[j] = doc[j-1];
			
			doc[i+1] = aux;	

			break;
		}
	}

}

int le(CPF* doc, char* nomeArq){

   int a, b = 0, c = 0;
   FILE* arq;
   char prox[100];

	arq = fopen(nomeArq, "r");

	a = fscanf(arq, "%s", prox);
   
   while(a != EOF){   	
		b++;

		strcpy(doc[c].num, prox);
		fgetc(arq);

      fgets((doc[c]).nome, 100, arq);
      
      fscanf(arq, "%d", &(doc[c]).idade);

		a = fscanf(arq, "%s", prox);

		if (c > 0){
			ordena(doc, c);
		}
		
		c++;
 
   }

	fclose(arq);
	

	return b;

}

void printar(CPF* doc1, int tam1, CPF* doc2, int tam2) {

	int i = 0, j = 0, c;
	
	while (i < tam1 && j < tam2){
		if (strcmp((doc1[i]).num, (doc2[j]).num) < 0){
			printf("%s\n%s%d\n", (doc1[i]).num, (doc1[i]).nome, (doc1[i]).idade);
			i++;
		}
		else {
			printf("%s\n%s%d\n", (doc2[j]).num, (doc2[j]).nome, (doc2[j]).idade);
			j++;
		}
	}
	
	for (c = i; c < tam1; c++)
		printf("%s\n%s%d\n", (doc1[c]).num, (doc1[c]).nome, (doc1[c]).idade);

	for (c = j; c < tam2; c++)
		printf("%s\n%s%d\n", (doc2[c]).num, (doc2[c]).nome, (doc2[c]).idade);
	
}

int main () {

	int tam1, tam2;
   CPF* doc1 = NULL;
	CPF* doc2 = NULL;
   char nomeArq1[100], nomeArq2[100];
   
	doc1 = malloc(10*sizeof(CPF));
	doc2 = malloc(10*sizeof(CPF));

   scanf("%s", nomeArq1);
   getchar();
   scanf("%s", nomeArq2);

   tam1 = le(doc1, nomeArq1);
	tam2 = le(doc2, nomeArq2);	

	printar(doc1, tam1, doc2, tam2);

	free(doc1);
	free(doc2);

   return 0;

}
