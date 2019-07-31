#include <stdio.h>
#include <string.h>

int main () {

   char assunto[100];
   char data [3][4];
   char horario [3][4];
   int total, i;

   scanf("%d", &total);

   for (int n = 0; n != total; n++){
      for (i = 0; i < 3; i++){
         scanf("%s", data[i]);
      }

      for (i = 0; i < 3; i++){
         scanf("%s", horario[i]);
         getchar();
      }
	  fgets(assunto, 100, stdin);
      assunto[strlen(assunto)-1] = '\0';
      printf("%s/%s/%s - %s:%s:%s\n", data[0], data[1], data[2], horario[0], horario[1], horario[2]);
      printf("%s\n", assunto);
   }

   return 0;

}
