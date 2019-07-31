#include <stdio.h>
#include <math.h>

int main () {

    long int N;
    double n;
    long int i;
    double vet[100000];
    double resul;
    long int k = 0;

    scanf("%ld", &N);

    for (i=0; i<N; i++) {
        scanf("%lf", &vet[i]);
    }
    for (k=0; k<=N-1; k++) {
        n = 0;
        resul = 0;
        for (i=0; i<N; i++) {
            resul += vet[i]*cos((M_PI*k*(2.0*n+1))/(2*N));
            n++;
        }
        printf ("%.6lf\n", resul);
    }

    return 0;

}
