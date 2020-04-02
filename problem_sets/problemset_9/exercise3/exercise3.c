#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>


int main(int argc, char const *argv[]) {
  int i, N = 100000;
  double s = 0.;

  double *a = (double*)malloc(N*sizeof(double));
  double *b = (double*)malloc(N*sizeof(double));
  a[0] = 10;
  s += a[0];
  #pragma omp parallel for private(i) reduction(+:s)
  for (i = 1; i < N-1; i++){
    a[i] = cos(20.0 + sin(0.1*(i-1)));
    s += a[i];
  }
  //s += cos(20.0 + sin(0.1*(i-1)))
  printf("s = %lf\n", s);
  free(a); free(b);
  s = 0.;

  a = (double*)malloc(N*sizeof(double));
  b = (double*)malloc(N*sizeof(double));


  for (i = 0; i < N; i++){
    a[i] = 10.0 + 2*i;
    b[i] = 20.0 + sin(0.1*i);
  }

  for (i = 0; i < N-1; i++){
    s += a[i];
    a[i+1] = cos(b[i]);
  }
  printf("s = %lf\n", s);

  return 0;
}
