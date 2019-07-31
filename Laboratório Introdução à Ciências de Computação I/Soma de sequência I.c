#include <stdio.h>

int main () {

    int n;
    int i = 0;
    double geral;
    double soma;

    scanf("%d", &n);

    while (i<=n) {
        geral = (double)i/(n-i+1);
        soma += geral;
        i++;
    }

    printf("%.4lf", soma);


}
