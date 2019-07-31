#include <stdio.h>

int main () {

   FILE * arq;
   char nomeArq [15];
   int numCaracter = -1;
   
   scanf("%s", nomeArq);

   arq = fopen (nomeArq, "r");

   while(!feof(arq)){
      fread(nomeArq, 1, 1, arq);
      numCaracter++;
   }

   printf("%d", numCaracter);

   return 0;

}
