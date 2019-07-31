#include <stdio.h>

int main () {

    float a;
    char b;
    float c;

    scanf("%f %c %f", &a, &b, &c);

    switch (b) {

    case '+':
        printf("%.2f", a + c);
        break;

    case '-':
        printf("%.2f", a - c);
        break;

    case '*':
        printf("%.2f", a * c);
        break;

    case '/':
        printf("%.2f", a / c);
        break;

    }

}
