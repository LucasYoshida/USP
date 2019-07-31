#include <stdio.h>
#include <math.h>

int main () {

    float a;
    float b;
    float c;
    float delta;
    float parte;
    float n1;
    float n2;

    scanf ("%f %f %f", &a, &b, &c);

    delta = pow(b, 2) - (4*a*c);
    parte = (-b)/(2*a);
    n1 = (-b - sqrt(delta))/(2*a);
    n2 = (-b + sqrt(delta))/(2*a);

    if (delta < 0)
    {
        printf("NAO EXISTE RAIZ REAL");
    }
        else if (delta==0){
            printf("%.3f", parte);
        }
        else if (delta > 0)
        {
            printf("%.3f %.3f", n1, n2);
        }

    return 0;

}
