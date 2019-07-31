#include <stdio.h>
#include <math.h>

int main () {

	int n;
	int i = 2;
	int div;
	int raiz;
    double soma=0;
    int sinal = 1;
    double frac;

	scanf("%d", &n);

	while(i<=n){
		raiz = sqrt(i);
		div=1;
		while(div<=raiz){
			if(div!=1 && i%div == 0)
				break;
			if(div==raiz) {
                frac = (1.0/i);
                soma = soma + sinal*frac;
                sinal = sinal*-1;
			}
			div++;
		}
		i++;
	}
    printf ("%.7lf", soma);

	return 0;
}
