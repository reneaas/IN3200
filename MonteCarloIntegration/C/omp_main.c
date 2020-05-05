#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
  int N = 10000000, max_int = 10000000;
  double max_inv, x, y, alpha, beta, alpha_inv, beta_inv, integral = 0;
  double tmp1, tmp2;
  max_inv = 1.0/max_int;
  alpha = 1;
  beta = 0.5;
  alpha_inv = 1./alpha;
  beta_inv = 2;
  double start, end, timeused;

  start = omp_get_wtime();
  #pragma omp parallel for reduction(+:integral)
  for (int i = 0; i < N; i++){
    x = (rand() % max_int)*max_inv;
    y = (rand() % max_int)*max_inv;

    x = -alpha_inv*log(1-x);
    y = -beta_inv*log(1-y);

    integral += 1./(1 + x*x + y*y);

  }
  end = omp_get_wtime();
  timeused = end-start;
  printf("\n");
  printf("Timeused = %lf\n", timeused);
  return 0;
}
