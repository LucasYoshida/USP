#include <stdio.h>

int main () {

    int n;
    double den;
    int i;
    double vet[10000];
    double media;
    double frac;

    scanf("%d", &n);

    for(i=0;i<n;i++){
        scanf ("%lf", &vet[i]);
        frac = vet[i] + 1;
        den += 1/frac;
    }

    media = (n/den)-1;

    printf("%.2lf", media);

    return 0;

}
