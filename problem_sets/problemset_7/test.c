#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  int n = 100;
  int n_start = 50;
  int n_end = n - n_start;
  double *x = (double*)malloc(n*sizeof(double));
  double *x_local = &x[50];
  for (int i = 0; i < n; i++) x[i] = i;


  for (int i = 0; i < n_end; i++) printf("x_local[%d] = %lf\n", i, x_local[i]);

  return 0;
}
