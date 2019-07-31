#include <stdio.h>

int main () {

    int a, b;
    int m, n;
    int mat_pri[100][100];
    int c, d;
    int mat_sec[100][100];
    int o;
    int resultado [100][100] = {0};
    int soma;

    scanf("%d %d", &a, &b);

    for (m = 0; m < a; m++){
        for(n = 0; n < b; n++){
            scanf("%d", &mat_pri[m][n]);
        }
    }

    scanf("%d %d", &c, &d);

    for (m = 0; m < c; m++){
        for(n = 0; n < d; n++){
            scanf("%d", &mat_sec[m][n]);
        }
    }

    for (m = 0; m < a; m++){
        for(n = 0; n < d; n++){
            for(o = 0; o < b; o++){
                soma = mat_pri[m][o] * mat_sec[o][n];
                resultado[m][n] += soma;
            }
            printf("%d ", resultado[m][n]);
        }
        printf("\n");
    }
    return 0;

}

