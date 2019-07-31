#include <stdio.h>
#include <math.h>

int main () {

    int vet[10000];
    int j;
    int i;
    int l;
    int soma = 0;
    int k = 0;
    double media;

    for(i=0; i<=1000; i++) {
        scanf ("%d", &vet[i]);
        soma += vet[i];
        if(vet[i]==0) {
            media = soma/(double)i;
            break;
        }
    }

    for (j=1; j<i-1; j++){
        l = vet[k]+vet[k+1]+vet[k+2];
        printf("%.4lf\n",(double)pow(vet[j],2)/(media*((double)l/3)));
        k++;
    }

    return 0;

}
