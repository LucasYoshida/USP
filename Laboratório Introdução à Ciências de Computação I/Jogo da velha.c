#include <stdio.h>

int verifica (int jojo[3][3]){

   for (int o = 0; o < 3; o++){
      if(jojo[o][0] == jojo[o][1] && jojo[o][0] == jojo[o][2] && jojo[o][1] == jojo[o][2]){
         return jojo[o][0];
      }
      else if(jojo[0][o] == jojo[1][o] && jojo[0][o] == jojo[2][o] && jojo[1][o] == jojo[2][o]){
         return jojo[0][o];
      }
   }
   
   if(jojo[0][0] == jojo[1][1] && jojo[0][0] == jojo[2][2] && jojo[1][1] == jojo[2][2]){
      return jojo[0][0];
   }
   else if(jojo[0][2] == jojo[1][1] && jojo[0][2] == jojo[2][0] && jojo[1][1] == jojo[0][2]){
      return jojo[0][2];
   }
   
   return 3;

}

int main () {

   int jojo[3][3];
   int m, n;
   int x = 2;

   for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){
         jojo[i][j] = x;
         x++;
      }
   }

   for (int i = 0; i < 9;i++){
      
      scanf("%d %d", &m, &n);
      
      jojo[m][n] = (i%2);
     
      x = verifica(jojo);
      
      if(x == 0 || x == 1){
        printf("%d",x);
        break;
      }

   }
   
   if(x == 3){
      printf("empate");
   }

}
      
      
       
