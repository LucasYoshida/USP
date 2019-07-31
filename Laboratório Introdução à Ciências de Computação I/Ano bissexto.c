#include <stdio.h>

int main () {

    int a;
    int b;
    int c;
    int d;

    scanf("%d", &a);

    b = a % 4;
    c = a % 100;
    d = a % 400;

    if (((b == 0) && (c != 0)) || (d == 0)){
        printf("SIM");
    }
    else {
        printf("NAO");
    }

return 0;

}
