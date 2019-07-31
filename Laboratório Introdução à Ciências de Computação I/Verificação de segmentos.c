#include <stdio.h>
#include <math.h>

int main () {

  int primeiro;
  int segundo;
  int l = 1, n = 10, m = 10;
  int a, b;
  int menor = 0;

  scanf("%d", &primeiro);

  scanf("%d", &segundo);

  if(primeiro>=segundo){
    menor = segundo;
  }
  else if(segundo>=primeiro){
    menor = primeiro;
  }

  while (menor>10){
    n = pow(10,l);
    l++;
    menor = menor/10;
    m = n*10;
  }

  l = 4;

  if(primeiro>=segundo){
      a  = primeiro/n;
      b  = primeiro%m;
    while(a>=1){
      if (segundo==a || segundo == b){
        l = 0;
        break;
      }
      else{
        l = 1;
      }
      b = a%m;
      a = a/n;
    }
  }

  else if(segundo>=primeiro){
    a  = segundo/n;
    b  = segundo%m;
    while(a>=1){
      if (primeiro==a || primeiro == b){
        l = 2;
        break;
      }
      else{
        l = 3;
      }
      b = a%m;
      a = a/n;
    }
  }

  if(l == 0){
    printf("%d %d SIM", segundo, primeiro);
  }
  else if(l == 1){
    printf("%d %d NAO", segundo, primeiro);
  }
  else if (l==2){
    printf("%d %d SIM", primeiro, segundo);
  }
  else if (l==3){
    printf("%d %d NAO", primeiro, segundo);
  }


  return 0;

}
