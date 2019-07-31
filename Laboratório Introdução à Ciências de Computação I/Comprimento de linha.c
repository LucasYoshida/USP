#include <stdio.h>
#include <math.h>

float distancia (int n) {

  float total = 0;
  float r = 0;
  int i;
  float raiz[100];
  float ponto[100];

  for (i = 0; i<2*n; i++){
    scanf("%f", &ponto[i]);
  }	

  for (i = 0; i<(2*n)-2; i++){
    raiz[i] = pow((ponto[i]-ponto[i+2]),2);
  }
  
  for (i = 0; i<(2*n)-2; i+=2){
    total=sqrt(raiz[i]+raiz[i+1]);
    r += total; 
  }
  
  return r;
}

int main () {
  
  int n;
  float resultado;
  
  scanf ("%d", &n);
  
  resultado = distancia (n);
  
  printf("%.4f", resultado);
  
  return 0;
  
}