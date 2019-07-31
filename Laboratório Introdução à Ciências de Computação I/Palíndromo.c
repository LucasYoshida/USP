#include <stdio.h>
#include <string.h>

int main () {

    char str[10000];
    int i;
    int n = 0;
    int x;

    scanf("%s", str);

    x = strlen(str)-1;

        for (i = 0; i<strlen(str); i++){
            if (str[i]==str[x]){
                n ++;
            }
            x -= 1;
        }

    if (n == strlen(str)) {
        printf("SIM");
    }
    else {
        printf("NAO");
    }

    return 0;

}
