#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
  double *a, *b;
  int n = 10000000;
  a = (double*)malloc(n*sizeof(double));
  b = (double*)malloc(n*sizeof(double));
  clock_t start, end;
  double timeused_function, timeused_bf;

  for (int i = 0; i < n; i++)
  {
    a[i] = i;
  }

  start = clock();
  memcpy(b, a, n*sizeof(double));
  end = clock();
  timeused_function = (double) (end-start)/CLOCKS_PER_SEC;


  start = clock();
  for (int i = 0; i < n; i++)
  {
    b[i] = a[i];
  }
  end = clock();
  timeused_bf = (double) (end-start)/CLOCKS_PER_SEC;

  printf("timeused by function = %lf \n", timeused_function);
  printf("timeused by brute force = %lf \n", timeused_bf);
  return 0;
}
