#include <stdio.h>



int main () {

  
int entrada;

  int a, b;

  int soma = 0;


  
scanf("%d", &entrada);

  
  a = entrada;

  b = entrada;

  
  
  while(a>=1){

    b = a%10;

    soma+=b;

    a = a/10;

  }

  
  
  printf("%d", soma);

  
  
  return 0;


}