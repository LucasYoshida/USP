#include <stdio.h>
#include <string.h>

int resultado (char nome[10000], char caracter){

    int m;
    int resultado = 0;

    for (m = 0; m<strlen(nome); m++){
        if(nome[m]==caracter){
            resultado++;
        }
    }

    return resultado;

}

int main () {

    char nome [10000];
    char caracter;
    int saida;

    fgets(nome, 10000, stdin);

    scanf("%c", &caracter);
    saida = resultado(nome, caracter);

    printf("%d", saida);

    return 0;

}
