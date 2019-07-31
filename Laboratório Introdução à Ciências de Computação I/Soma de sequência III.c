#include <stdio.h>

int main () {

    int n;
    int i;
    int num = 1;
    int a = 0;
    int den;
    double frac;
    double soma = 0;

    scanf("%d", &n);

    for (i = 1; i<=n; i++) {
        den = n - a;
        frac = (float)num/den;
        soma += frac;
        num += 2;
        a++;
    }
    printf ("%.4lf", soma);

    return 0;

}
