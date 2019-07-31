#include <stdio.h>

int main () {

    int vet[31];
    int i;
    int maior;

    for (i=0; i<=30; i++) {
        scanf("%d", &vet[i]);
    }

    maior = vet[0];

    for (i = 0; i<=30; i++) {
            if(maior<=vet[i]){
                maior = vet[i];
            }
        }
    printf("%d\n", maior);

    for (i = 0; i<=30; i++) {
        if (vet[i] == maior){
            printf("%d\n", i+1);
        }
    }

    return 0;

}
