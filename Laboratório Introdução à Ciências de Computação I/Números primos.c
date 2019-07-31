#include <stdio.h>
#include <math.h>

int main () {

	int n;
	int i = 2;
	int div;
	int raiz;

	scanf("%d", &n);

	while(i<=n){
		raiz = sqrt(i);
		div=1;
		while(div<=raiz){

			if(div!=1 && i%div == 0)
				break;//nao e primo
			if(div==raiz)
				printf("%d ", i); //é primo
			div++;
		}
		i++;
	}

	return 0;
}
