#include <stdio.h>
#include <string.h>

int main () {

   int a, b, c;
   char frases[20][20], copyfrases[20][20], total[20];

   scanf("%d", &a);

   for (b = 0; b < a; b++){
	scanf("%s", frases[b]);
	strcpy (copyfrases[b], frases[b]);
   }

   for (b = 0; b < a; b++){
	for (c = b + 1; c < a; c++){
	   if(strcmp(frases[b], frases[c]) > 0){
		strcpy (total, frases[b]);
	   	strcpy (frases[b], frases[c]);
		strcpy (frases[c], total);
	   }
	}
   }

   for (b = 0; b < a; b++){
	printf("%s\n", frases[b]);
   }

   return 0;

}
