#include <stdio.h>

int main () {

   double first;
   double r;
   int K;
   double results[10000];

   scanf("%lf %lf %d", &first, &r, &K);

   results[0] = first;

   for (int i = 0; i < K; i++){
      results[i+1] = r * results[i] * (1 - results[i]);
      printf("%d %.6lf\n", i+1, results[i+1]);
   }

   return 0;

}
