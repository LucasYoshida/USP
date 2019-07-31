#include <stdio.h>
#include <math.h>

int main () {

   int n;
   char a = 0;
   double xCo, yCo;
   double xRa, yRa;
   double xBu[1000], yBu[1000];
   double distCo[1000];
   double distRa[1000];

   scanf("%d %lf %lf %lf %lf", &n, &xCo, &yCo, &xRa, &yRa);
   
   for(int cont = 0; cont < n; cont++){
      scanf("%lf %lf", &xBu[cont], &yBu[cont]);
   }

   for (int cont2 = 0; cont2 < n; cont2++){
      distCo[cont2] = sqrt(pow((xBu[cont2] - xCo), 2) + pow((yBu[cont2] - yCo), 2));
      distRa[cont2] = sqrt(pow((xBu[cont2] - xRa), 2) + pow((yBu[cont2] - yRa), 2)) / 2;
   
      if (distCo[cont2] <= distRa[cont2]){
         printf("O coelho pode escapar pelo buraco (%.3f,%.3f).\n", xBu[cont2], yBu[cont2]);
         a = 1;
         break;
      }
   }

   if (a == 0){
      printf("O coelho nao pode escapar.\n");
   }

   return 0;

}
  


