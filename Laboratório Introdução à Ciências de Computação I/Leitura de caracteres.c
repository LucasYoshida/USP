#include <stdio.h>
#include <stdlib.h>

int main () {
  
  char* nome;
  int m = 0;
  
  nome = (char*) malloc(10000);
  
  fgets (nome, 10000, stdin);
  
  for (m = 0; nome[m]!='\n'; m++){
    printf("%c\n", nome[m]);
  }  
  free (nome);
  
  return 0;
  
}