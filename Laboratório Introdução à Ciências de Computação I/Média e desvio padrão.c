#include <stdio.h>
#include <math.h>

int main () {

    long int n;
    long int i;
    long int soma = 0;
    double media = 0;
    double geral;

    scanf ("%ld", &n);

    double N [n];

    for (i = 0; i < n; i++) {
        scanf ("%lf", &N[i]);
        soma += N[i];
        geral = N[i]/(double)n;
        media += geral;
    }
    printf("%.4lf\n", media);

    double geral1;
    double desvio = 0;
    double desviop;

    for (i = 0; i < n; i++) {
        geral1 = pow((N[i]-media), 2)/(double)n;
        desvio += geral1;
    }
    desviop = sqrt(desvio);
    printf("%.4lf", desviop);

return 0;

}
