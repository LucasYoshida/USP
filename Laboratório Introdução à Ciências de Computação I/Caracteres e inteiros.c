#include <stdio.h>
#include <stdlib.h>

int main () {

  char* caracteres;;
  int n = 0, o = 0;
  char num;
  int i, inteiro;

  //aloca na heap
  caracteres = malloc(100000000*sizeof(char));

  //inserir os caracteres
  while (n<100000000){
	  scanf("%c", &caracteres[n]);
	  getchar();
	  if (caracteres[n] == 'x'){
      for (i = 0; i != o; i++){
	      if (caracteres[o] <= caracteres [i]){
	         num = caracteres[o];
	         caracteres[o] = caracteres[i];
	         caracteres[i] = num;
	      }
	    }
	    o++;
      break;
	  }
	  for (i = 0; i != o; i++){
	      if (caracteres[o] < caracteres [i]){
	         num = caracteres[o];
	         caracteres[o] = caracteres[i];
	         caracteres[i] = num;
	      }
	  }
	  o++;
	  n++;
  }

  //fazer o bitwise
  for(i = 0; i < o; i++){
	  inteiro = 0;
	  inteiro |= (caracteres[i+3]<<24);
	  inteiro |= (caracteres[i+2]<<16);
	  inteiro |= (caracteres[i+1]<<8);
	  inteiro |= (caracteres[i]);
	  i+=3;
	  printf("%d\n", inteiro);
  }

  //libera a heap
  free(caracteres);

  return 0;

}
