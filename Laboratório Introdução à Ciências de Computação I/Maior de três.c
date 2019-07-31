#include <stdio.h>

int main(int argc, char* argv[]) {

	int a;
	int b;
	int c;

	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	if (a > b && a > c)
	printf ("%d", a);
		else if (a < c){
		printf("%d", c);
		}
		else if (b > c) {
		printf("%d", b);
	}
	else printf("%d", c);	
	

return 0;

}


