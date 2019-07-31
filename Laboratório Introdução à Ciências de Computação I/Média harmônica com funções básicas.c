#include <stdio.h>

int readInt(){
  
  int n;
  
  scanf("%d", &n);
  
  return n;
  
}

double readDouble(int n){
  
  double den;
  int i;
  double vet[10000];
  double media;
  double frac;
  
  for(i=0;i<n;i++){
    scanf ("%lf", &vet[i]);
    frac = vet[i] + 1;
    den += 1/frac;
  }

  media = (n/den)-1;
  
  return media;
  
}

void printDouble(double media){
  
  printf("%.2lf", media);

}

int main () {
  
  printDouble(readDouble(readInt()));

  return 0;

}