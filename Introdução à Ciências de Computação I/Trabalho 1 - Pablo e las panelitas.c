/* Trabalho 1 - ICC - Pablo na USC

    Lucas N Yoshida - 10262586
*/

#include <stdio.h>

int main () {

    int k;
    int n;
    int b1, b2;
    int c1, c2;
    int d1, d2;
    int e1, e2;
    int f1, f2;
    int g1, g2;
    int h1, h2;
    int j1, j2;
    int x, y;

    scanf("%d", &k);
    scanf("%d", &n);

    //contas necessárias para transformar um decial em bionário

        b1 = n % 2;
        b2 = n / 2;
        c1 = b2 % 2;
        c2 = b2 / 2;
        d1 = c2 % 2;
        d2 = c2 / 2;
        e1 = d2 % 2;
        e2 = d2 / 2;
        f1 = e2 % 2;
        f2 = e2 / 2;
        g1 = f2 % 2;
        g2 = f2 / 2;
        h1 = g2 % 2;
        h2 = g2 / 2;
        j1 = h2 % 2;
        j2 = h2 / 2;
        x = b1+c1+d1+e1+f1+g1+h1+j1;
        y = 8-x;

        if ((k<0 || k>3) || (n<0 || n>1000000000)){
            printf("Invalid input\n");}

            //dependendo do valor de k a quantidade de vezes que as contas são feitas muda
            //k==0 (1vez=primeiro byte), k==1 (2vezes=segundo byte), k==2 (3vezes=terceiro byte), k==3 (4vezes=quarto byte)

            else if ((k==0) && (n>=0 || n<=1000000000)) {
                printf("%d%d%d%d%d%d%d%d\n", b1, c1, d1, e1, f1, g1, h1, j1);
                printf("%d\n", y);
                printf("%d\n", x);}

            else if ((k==1) && (n>=0 || n<=1000000000)) {
                b1 = j2 % 2;
                b2 = j2 / 2;
                c1 = b2 % 2;
                c2 = b2 / 2;
                d1 = c2 % 2;
                d2 = c2 / 2;
                e1 = d2 % 2;
                e2 = d2 / 2;
                f1 = e2 % 2;
                f2 = e2 / 2;
                g1 = f2 % 2;
                g2 = f2 / 2;
                h1 = g2 % 2;
                h2 = g2 / 2;
                j1 = h2 % 2;
                j2 = h2 / 2;
                x = b1+c1+d1+e1+f1+g1+h1+j1;
                y = 8-x;
                printf("%d%d%d%d%d%d%d%d\n", b1, c1, d1, e1, f1, g1, h1, j1);
                printf("%d\n", y);
                printf("%d\n", x);}

            else if ((k==2) && (n>=0 || n<=1000000000)) {
                b1 = j2 % 2;
                b2 = j2 / 2;
                c1 = b2 % 2;
                c2 = b2 / 2;
                d1 = c2 % 2;
                d2 = c2 / 2;
                e1 = d2 % 2;
                e2 = d2 / 2;
                f1 = e2 % 2;
                f2 = e2 / 2;
                g1 = f2 % 2;
                g2 = f2 / 2;
                h1 = g2 % 2;
                h2 = g2 / 2;
                j1 = h2 % 2;
                j2 = h2 / 2;
                b1 = j2 % 2;
                b2 = j2 / 2;
                c1 = b2 % 2;
                c2 = b2 / 2;
                d1 = c2 % 2;
                d2 = c2 / 2;
                e1 = d2 % 2;
                e2 = d2 / 2;
                f1 = e2 % 2;
                f2 = e2 / 2;
                g1 = f2 % 2;
                g2 = f2 / 2;
                h1 = g2 % 2;
                h2 = g2 / 2;
                j1 = h2 % 2;
                j2 = h2 / 2;
                x = b1+c1+d1+e1+f1+g1+h1+j1;
                y = 8-x;
                printf("%d%d%d%d%d%d%d%d\n", b1, c1, d1, e1, f1, g1, h1, j1);
                printf("%d\n", y);
                printf("%d\n", x);}

            else if ((k==3) && (n>=0 || n<=1000000000)){
                b1 = j2 % 2;
                b2 = j2 / 2;
                c1 = b2 % 2;
                c2 = b2 / 2;
                d1 = c2 % 2;
                d2 = c2 / 2;
                e1 = d2 % 2;
                e2 = d2 / 2;
                f1 = e2 % 2;
                f2 = e2 / 2;
                g1 = f2 % 2;
                g2 = f2 / 2;
                h1 = g2 % 2;
                h2 = g2 / 2;
                j1 = h2 % 2;
                j2 = h2 / 2;
                b1 = j2 % 2;
                b2 = j2 / 2;
                c1 = b2 % 2;
                c2 = b2 / 2;
                d1 = c2 % 2;
                d2 = c2 / 2;
                e1 = d2 % 2;
                e2 = d2 / 2;
                f1 = e2 % 2;
                f2 = e2 / 2;
                g1 = f2 % 2;
                g2 = f2 / 2;
                h1 = g2 % 2;
                h2 = g2 / 2;
                j1 = h2 % 2;
                j2 = h2 / 2;
                b1 = j2 % 2;
                b2 = j2 / 2;
                c1 = b2 % 2;
                c2 = b2 / 2;
                d1 = c2 % 2;
                d2 = c2 / 2;
                e1 = d2 % 2;
                e2 = d2 / 2;
                f1 = e2 % 2;
                f2 = e2 / 2;
                g1 = f2 % 2;
                g2 = f2 / 2;
                h1 = g2 % 2;
                h2 = g2 / 2;
                j1 = h2 % 2;
                j2 = h2 / 2;
                x = b1+c1+d1+e1+f1+g1+h1+j1;
                y = 8-x;
                printf("%d%d%d%d%d%d%d%d\n", b1, c1, d1, e1, f1, g1, h1, j1);
                printf("%d\n", y);
                printf("%d\n", x);}

return 0;




}
