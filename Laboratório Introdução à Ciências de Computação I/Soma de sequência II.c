#include <stdio.h>

int main () {

    int n;
    double i = 1;
    int sinal = 1;
    double frac;
    double soma = 0;

    scanf("%d", &n);

    while (i<=n) {
        frac = 1/i;
        soma += sinal*frac;
        sinal *= -1;
        i++;
    }
    printf("%.4lf", soma);

    return 0;

}


