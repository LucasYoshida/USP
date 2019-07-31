#include <stdio.h>

int main() {

    int a;
    int b;
    int c;
    int quo;
    int res;

    scanf("%d", &a);
    scanf("%d", &b);

    quo = 0;
    c = 0;

    if (a<b) {
        printf ("%d\n%d", c, c);
        return 0;
    }

    while (a>=b) {
        quo++;
        res = a-b;
        a = res;
    }
    printf ("%d\n%d\n", quo, res);

return 0;

}
