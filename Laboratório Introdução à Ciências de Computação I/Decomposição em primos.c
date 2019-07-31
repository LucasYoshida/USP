#include <stdio.h>

int main(void) {
       int n;
       int a = 2;
       int b;
       int primo;
       int div;

       scanf("%d", &n);

       while (n > 1) {
            b = 0;
            while (n % a == 0) {
                b = b + 1;
                n = n / a;
             }
            if (b > 0)
                printf("%d %d\n", a, b);
                primo = 0;
            while (! primo) {
                a = a + 1;
                div = 2;
                primo = 1;
                while (div <= a / 2 && primo) {
                    if (a % div == 0)
                        primo = 0;
                    else
                        div = div + 1;
                }
            }
     }

   return 0;

}
