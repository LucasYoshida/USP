#include <stdio.h>

int main () {
  
  int entrada;
  int mat[10][10];
  int linha[10] = {0};
  int coluna[10] = {0};
  int diagonal[2] = {0};
  int l = 0, k = 0;
  int n, m;
  
  scanf("%d", &entrada);
  
  for(n = 0; n<entrada; n++){
    for(m = 0; m<entrada; m++){
      scanf("%d", &mat[n][m]);
    }
  }
  
  for(n = 0; n<entrada; n++){
    for(m = 0; m<entrada; m++){
      linha[n] += mat[n][m];
    }
  }
  
  m = 0;
  
  for(n = 1; n<entrada; n++){
    if(linha[entrada-1] == linha[entrada-n]){
      m++;
    }
    if(m == entrada-1){
      l++;
    }
  }
  
  for(m = 0; m<entrada; m++){
    for(n = 0; n<entrada; n++){
      coluna[m] += mat[n][m];
    }
  }
  
  m = 0;
  
  for(n = 1; n<entrada; n++){
    if(coluna[entrada-1] == coluna[entrada-n]){
      m++;
    }
    if(m == entrada-1){
      l++;
    }
  }
  
  
  for(n = 0; n<entrada; n++){
    diagonal[k] += mat[n][n];
  }
  
  k++;
  
  for(n = entrada-1; n>=0; n--){
    diagonal [k] += mat[n][entrada-n-1];
  }
  
  if(diagonal[0]==diagonal[1]){
    l++;
  }
  
  if(l==3){
    printf("SIM");
  }
  
  else {
    printf("NAO");
  }
  
  return 0;
  
}