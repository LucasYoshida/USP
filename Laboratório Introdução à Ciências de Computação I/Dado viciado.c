#include <stdio.h>

int main () {

    int i = 0;
    int lidos[1000] = {0};
    int var;
    int n = 0;
    int k = 0;
    int j = 0;
    int m = 0;
    int saida = 0;
    int maior[6];

    for (i = 0; var != EOF; i++){
        var = scanf("%d", &lidos[i]);
        m++;
    }

    for (j = 1; j < 7; j++){
    	k = 0;
        for (i = 0; i<m-1 ; i++){
        	if (j== lidos[i]){
        		k++;
        	}
        }
        maior[n] = k;
        n++;
    }

    saida  = maior[0];

    for (n = 0; n <6; n++){
    		if (saida <= maior[n]){
    			saida  = maior[n];
    		}
	 	}

    for (n = 0; n < 6; n++){
    	if (saida == maior[n]){
    		printf("%d\n", n+1);
    	}
    }

    printf("%d", saida);

    return 0;

}
