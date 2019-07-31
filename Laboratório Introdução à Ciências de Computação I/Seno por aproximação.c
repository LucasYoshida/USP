#include <stdio.h>
#include <math.h>

int main () {

    double n;
    int i = 1;
    double num;
    int j = 1;
    int sinal = 1;
    double soma=0;
    int a=1;

    scanf("%lf", &n);


    while (a<=300) {
        num = pow(n,i);
        j=1;
        while (j<=i) {
            num = num / j;
            j++;
        }
        soma += sinal*num;
        sinal *= -1;
        i+=2;
        a++;
    }
    printf("%.6lf", soma);

}
