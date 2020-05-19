#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[]) {
  int N = 100000000;
  double N_div = 1.0/N;
  double *a = malloc(N*sizeof *a);
  for (int i = 0; i < N; i++){
    a[i] = 0.0001*i;
  }

  double norm = 0;
  double start = omp_get_wtime();
  #pragma omp parallel for reduction(+:norm)
  for (int i = 0; i < N; i++){
    norm += a[i]*a[i];
  }
  norm = sqrt(norm);
  double end = omp_get_wtime();
  double timeused = end-start;
  printf("Time used = %lf\n", timeused);
  printf("Norm = %lf\n", norm);


  norm = 0;
  for (int i = 0; i < N; i++){
    norm += a[i]*a[i];
  }
  norm = sqrt(norm);
  printf("Actual norm = %lf\n", norm);
  return 0;
}
