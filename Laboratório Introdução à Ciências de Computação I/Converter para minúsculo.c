#include <stdio.h>
#include <string.h>
int main(){

    char i;
    int j = 0;
    char ent[10000];

    scanf("%s", ent);

    while (j<=strlen(ent)){
        for (i = 65; i <= 90; i++){
            if (ent[j]==i){
                printf("%c", i+32);
            }
        }
        j++;
    }


    return 0;
}
