#include <stdio.h>
#include <math.h>

int main () {

   int numeros;
   int a, b;
   int soma = 0;

   for (numeros = 1000; numeros<=9999; numeros++){
	a = numeros / 100;
	b = numeros % 100;
	soma = b;
	b = a % 100;
	soma += b;
	if (sqrt(numeros)==soma){
	   printf("%d\n", numeros);
	}
   }

   return 0;

}
