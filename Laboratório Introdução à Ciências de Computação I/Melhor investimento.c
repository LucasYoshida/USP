#include <stdio.h>
#include <math.h>

int main () {

    double inicial;
    double juros1, juros2, juros3, juros4;
    long int periodo;
    double rendimento1, rendimento2, rendimento3;
    double P, L, C;

    scanf("%lf %ld", &inicial, &periodo);

    juros1 = 1.0059;
    juros2 = 1.0086;
    juros3 = 1.01032;

    rendimento1 = inicial * pow(juros1, periodo);
    printf("%.2lf\n", P = rendimento1);

    if (periodo < 6) {
        printf("%.2lf\n", L = inicial);
        }
    else {
        rendimento2 = inicial * pow(juros2, periodo);
        printf("%.2lf\n", L = rendimento2);
        }

    if (periodo>=1 && periodo<=6) {
        juros4 = 0.225;
        rendimento3 = inicial * pow(juros3, periodo);
        C = rendimento3 - juros4 * (rendimento3-inicial);
        printf("%.2lf\n", C);
        }
        else if (periodo>=7 && periodo<=12) {
        juros4 = 0.2;
        rendimento3 = inicial * pow(juros3, periodo);
        C = rendimento3 - juros4 * (rendimento3-inicial);
        printf("%.2lf\n", C);
        }
        else if (periodo>=13 && periodo<=24) {
        juros4 = 0.175;
        rendimento3 = inicial * pow(juros3, periodo);
        C = rendimento3 - juros4 * (rendimento3-inicial);
        printf("%.2lf\n", C);
        }
        else if (periodo>24) {
        juros4 = 0.15;
        rendimento3 = inicial * pow(juros3, periodo);
        C = rendimento3 - juros4 * (rendimento3-inicial);
        printf("%.2lf\n", C);
        }

    if (L>=P && L>=C) {
        printf("L\n");
    }
        else if (P>=L && P>=C) {
            printf("P\n");
        }
        else if (C>=P && C>=L)
            printf("C\n");

return 0;

}
