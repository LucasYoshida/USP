#include <stdio.h>

int main () {

  int a;
  int i, j, estaVet, tam_vet = 0;
  double p1, p2;
  double entrada, vet[1000][2];

  scanf("%d", &a);

  for(i = 0; i < a; i++){
    scanf("%lf", &entrada);
    estaVet=0;
    for (j = 0; j<tam_vet; j++){
      if (entrada==vet[j][0]){
        estaVet = 1;
        vet[j][1]++;
      }
    }
    if(!estaVet){
      vet[tam_vet][0] = entrada;
      vet[tam_vet][1] = 1;
      tam_vet++;
    }
  }

  for(i=0; i<tam_vet; i++){
    for(j=i+1; j<tam_vet; j++){
      if(vet[i][0] > vet[j][0]){
        p1 = vet[i][0];
        vet[i][0] = vet[j][0];
        vet[j][0] = p1;
        p2 = vet[i][1];
        vet[i][1] = vet[j][1];
        vet[j][1] = p2;
      }
    }
  }
  
  for(i = 0; i < tam_vet; i++){
    printf("%.1lf %d\n", vet[i][0],(int)vet[i][1]);
  }

  return 0;

}