#include <stdio.h>

int main () {

   FILE * arq;
   int tamanho;
   char nomeArq [15];

   scanf("%s", nomeArq);

   arq = fopen(nomeArq, "r");

   fseek(arq, 0, SEEK_END);

   tamanho = ftell(arq);

   printf("%d", tamanho);

   return 0;

} 

 

