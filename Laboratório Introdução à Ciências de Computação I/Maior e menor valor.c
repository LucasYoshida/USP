#include <stdio.h>

int main () {

    int n;
    int maior;
    int menor;
    int quant;
    int i;

    scanf("%d", &quant);

    for (i=1; i<=quant; i++) {
        scanf("%d", &n);
        if (i == 1){
            maior = n;
            menor = n;
        }
        else if(i>=2){
            if (n>maior) {
                maior = n;
            }
            if (n<menor) {
                menor = n;
            }
        }
    }
    printf("max: %d\n", maior);
    printf("min: %d", menor);

return 0;

}
