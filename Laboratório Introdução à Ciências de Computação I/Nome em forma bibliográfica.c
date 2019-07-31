#include <stdio.h>
#include <string.h>

int main () {

    int m = 0;
    int p = 0;
    int o = 0;
    int k;
    char nome [10000];

    fgets (nome, 10000, stdin);
    //printf("%s", nome);

    k = strlen(nome)-1;
    //printf("%c", nome[k-8]);

    while (nome[k-1]!=' '){
       if (nome[k] >= 97){
                nome[k] -= 32;
            }
        o++;
        p++;
        k--;
        //printf("%s", nome);
        }

    while(o>0){
        printf("%c",nome[strlen(nome)-o-1]);
        o--;
        //printf("%s", nome);
    }

    printf(", ");

    for (m = 0; m < strlen(nome)-p-2; m++){
        printf("%c",nome[m]);
    }
    printf("\n");

    return 0;

}