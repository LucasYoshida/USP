#include <stdio.h>

int main () {

    char resp[100000] = {'*'};
    char j;
    int i;
    int n = 0;
    int m = 0;
    int o = 0;


    for (i = 0; i<=100000; i++){
         scanf("%c", &resp[i]);
         //printf("%d %c\n", i , resp[i]);
    }

    for (i = 0; i<=100000; i++){
        for (j = 65; j<=90; j++){
            if (resp[i]== j){
                n++;
            }
        }
        for (j = 97; j<=122; j++){
            if (resp[i]== j){
                m++;
            }
        }
        for (j = 48 ; j<=57; j++){
            if (resp[i]== j){
                o++;
            }
        }
    }
    printf("%d\n", n+m);
    printf("%d\n", o);

    return 0;

}
