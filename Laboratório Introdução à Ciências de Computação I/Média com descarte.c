#include <stdio.h>

int main () {

    double a;
    double b;
    double c;
    double d;

    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    if (a<=b && a<=c && a<=d) {
        printf("%.4lf", (b+c+d)/3);
    }
        else if (b<=a && b<=c && b<=d) {
            printf("%.4lf", (a+c+d)/3);
        }
        else if (c<=a && c<=b && c<=d) {
            printf("%.4lf", (a+b+d)/3);
        }
        else if (d<=a && d<=b && d<=c) {
            printf("%.4lf", (a+b+c)/3);
        }

return 0;

}
