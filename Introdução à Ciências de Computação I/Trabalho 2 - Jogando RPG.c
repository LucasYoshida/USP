#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {

    int m;          //numero de lutas
    int D;          //vida de Drizzt
    int vidaD;      //valor auxiliar para as condicoes, vida de Drizzt
    int A;          //vida de Artemis
    int vidaA;      //valor auxiliar para as condicoes, vida de Artemis
    int DDA;        //numero de faces de DDA
    int i;          //valor auxiliar para determinar a sequecias dos ataques
    int j;          //valor auxiliar para obtencao do valor de DA e o numero de dano pela espada
    int k;          //valor auxiliar para determinar a ordem de ataque
    int t = 1;      //valor auxiliar para contabilizar o numero de lutas
    int VRDDA [3];  //resultado de DDA em vetor, [0] para Drizzt, [1] para Artemis, [2] e [3] para autorização de ataque
    int DCA = 10;   //classe de armadura de Drizzt
    int ACA = 7;    //classe de armadura de Artemis
    int PC = 9;     //forca da arma (FA) da cimitarra e numero de faces de DA
    int PE = 7;     //forca da arma (FA) da espada e numero de faces de DA
    int VRDA [3];   //resultado de DA em vetor, para o ataque da cimitarra, [1]e[2] para primeiro e segundo ataque da espada
    int danoD;      //dano a ser dado pelo Drizzt
    int danoA;      //dano a ser dado pela Artemis
    int n = 0;      //valor auxiliar para ajudar na contabilização da batalha, representa quantas vezes Drizzy ganhou
    int o = 0;      //valor auxiliar para ajudar na contabilização da batalha, representa quantas vezes Artemis ganhou

    scanf("%d", &m);
    scanf("%d", &D);
    scanf("%d", &A);
    scanf("%d", &DDA);

    srand(pow(DDA, 2));

    for (t = 1; o <(m/2) + 1 && n <(m/2) + 1; t++) {
        printf("Luta %d\n", t);
        vidaD = D;
        vidaA = A;
        i = 2;
        for (k = 1; k < 3; k++) {  //verificar o maior valor de DDA para obter a ordem
            if (k == 1){
                VRDDA[0] = 1 + rand()%(DDA);
            }
            else{
                VRDDA[1] = 1 + rand()%(DDA);
            }
            if(VRDDA[0]>=VRDDA[1])
                i = 1;
            else
                i = 0;
        }
        while (vidaA>0 && vidaD>0) {
            if (i == 1) { //Drizzt ataca
                VRDDA[2] = 1 + rand()%DDA;  //ver a autorizacao do ataque
                    if (VRDDA[2] > ACA) {     //caso autorizado
                        VRDA[0] = 1 + rand() %  PC;
                            if (VRDA[0] == 1) {    //caso miss
                                danoD = 0;
                            }
                            else if (VRDA[0] == PC) {    //caso extra damage
                                danoD = 1.5*PC;
                                printf("Drizzt %d\n", danoD);
                            }
                            else {      //caso ataque normal
                                danoD = VRDA[0];
                                printf("Drizzt %d\n", danoD);
                            }
                            vidaA -= danoD;
                    }
                i = 0;
                if(vidaA<=0){
                    i = 2;
                }
            }
            if (i == 0) { //Artemis ataca
                VRDDA[2] = 1 + rand()%DDA;  //ver a autorizacao do ataque
                        if (VRDDA[2] > DCA) {     //caso autorizado
                            for (j = 1; j <= 2; j++) {
                                if (j == 1){
                                    VRDA[1] = 1 + rand() % PE;
                                }
                                else if(j==2){
                                    VRDA[2] = 1 + rand() % PE;
                                }
                            }
                            if (VRDA[1] == PE && VRDA[2] == PE) {    //caso extra damage
                                danoA = 3*PE;
                                printf("Artemis %d\n", danoA);
                            }
                            else if (VRDA[1] == 1 && VRDA[2] == 1) {    //caso miss
                                danoA = 0;
                            }
                            else {      //caso ataque normal
                                danoA = VRDA[1] + VRDA[2];
                                printf("Artemis %d\n", danoA);
                            }
                            vidaD -= danoA;
                    }
                i = 1;
                if(vidaA<=0){
                    i = 2;
                }
            }
        }
        if (vidaD <= 0) {
            printf("Fim da luta. Vencedor: Artemis\n");
            o++;
        }
        if (vidaA <= 0) {
            printf("Fim da luta. Vencedor: Drizzt\n");
            n++;
        }
    }

    if (o>n) {
        printf("Fim da batalha. Vencedor: ARTEMIS");
    }
    else if (n>o) {
        printf("Fim da batalha. Vencedor: DRIZZT");
    }

    return 0;

}

