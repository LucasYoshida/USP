#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a, b, m;
	
	scanf("%f", &a);
	scanf("%f", &b);

	m = 2/(1/(a+1)+1/(b+1))-1;

	printf("%.2f\n", m); 

	return EXIT_SUCCESS;

}
