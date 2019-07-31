#include <stdio.h>

typedef struct olimp{
   
   char pais [100][3];
   int ouro[100], prata[100], bronze[100];

}olimp;

void ordPais(olimp * medal, int i, int j){
   
   char country[3];
   
   for (int k = 0; k < 3; k++){
      country[k] = (*medal).pais[i][k];
      (*medal).pais[i][k] = (*medal).pais[j][k];
      (*medal).pais[j][k] = country[k];
   }

} 

void ordOuro(olimp * medal, int i, int j){ 
  
   int aux;

   aux = (*medal).ouro[i];
   (*medal).ouro[i] = (*medal).ouro[j];
   (*medal).ouro[j] = aux;

}

void ordPrata(olimp * medal, int i, int j){
 
   int aux;

   aux = (*medal).prata[i];
   (*medal).prata[i] = (*medal).prata[j];
   (*medal).prata[j] = aux;

}

void ordBronze(olimp * medal, int i, int j){
   
   int aux;

   aux = (*medal).bronze[i];
   (*medal).bronze[i] = (*medal).bronze[j];
   (*medal).bronze[j] = aux;

}

int main () {

   olimp medal;
   int paises;
 
   scanf("%d", &paises);

   for (int i = 0; i < paises; i++){
      scanf("%s %d %d %d", medal.pais[i], &medal.ouro[i], &medal.prata[i], &medal.bronze[i]);
     
   }
   
   for(int i = 0; i < paises; i++){
      for (int j = i+1; j < paises ; j++){
         if (medal.ouro[i] < medal.ouro[j]){
            ordOuro(&medal, i, j);
            ordPrata(&medal, i, j);
            ordBronze(&medal, i, j);
            ordPais(&medal, i, j);
         }
         else if(medal.prata[i] < medal.prata [j] && medal.ouro[i] == medal.ouro[j]){
            ordPrata(&medal, i, j);
            ordOuro(&medal,i, j);
            ordBronze(&medal, i, j);
            ordPais(&medal, i, j);
            }
         else if(medal.bronze[i] < medal.bronze[j] && medal.ouro[i] == medal.ouro[j] && medal.prata[i] == medal.prata[j]){
            ordBronze(&medal, i, j);
            ordOuro(&medal, i, j);
            ordPrata(&medal, i, j);
            ordPais(&medal, i, j);
         }
      }
   }

   for (int i = 0; i < paises; i++){
      printf("%c%c%c %d %d %d\n", medal.pais[i][0], medal.pais[i][1], medal.pais[i][2], medal.ouro[i], medal.prata[i], medal.bronze[i]);
   }

   return 0;

}

    

      

