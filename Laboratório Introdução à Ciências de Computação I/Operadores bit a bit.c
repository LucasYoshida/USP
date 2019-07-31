#include <stdio.h>

int main () {

    int a;
    int b;
    int c;
    int d;

    scanf("%d %d", &a, &b);

    printf("%d\n", a & b);
    printf("%d\n", a | b);
    printf("%d\n", a ^ b);
    printf("%d\n", c = ~ a);
    printf("%d\n", d = ~ b);
    printf("%d\n", a = a >> 2);
    printf("%d\n", b = b << 2);

return 0;

}
