#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
  int N = 1000000000, max_int = 10000;
  double max_inv, alpha, beta, alpha_inv, beta_inv, integral = 0;
  double tmp1, tmp2;
  max_inv = 1.0/max_int;
  alpha = 1;
  beta = 0.5;
  alpha_inv = 1./alpha;
  beta_inv = 1./beta;
  double start, end, timeused;
	//srand(1);
  srand(time(0)); //Set up random seed

  #ifdef _OPENMP
  {
    start = omp_get_wtime();
    #pragma omp parallel
    {
      double x,y;
      int id = omp_get_thread_num();
      int cache_line = 42;
      int seed = id + cache_line;
      #pragma omp for reduction(+:integral)
      for (int i = 0; i < N; i++){
        x = (rand_r(&seed) % max_int)*max_inv;  //Used instead of rand() to avoid false sharing.
        y = (rand_r(&seed) % max_int)*max_inv;  //Used instead of rand() to avoid false sharing.

        x = -alpha_inv*log(1-x);
        y = -beta_inv*log(1-y);

        integral += 1./(1 + x*x + y*y);

      }
    }
    end = omp_get_wtime();
    timeused = end-start;
    printf("\n");
    printf("Timeused = %lf\n", timeused);
  }
  #else
  {
    double x, y;
    start = clock();
    for (int i = 0; i < N; i++){
      x = (rand() % max_int)*max_inv;
      y = (rand() % max_int)*max_inv;

      x = -log(1-x)*alpha_inv;
      y = -log(1-y)*beta_inv;

      integral += 1./(1 + x*x + y*y);

    }
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("\n");
    printf("Timeused = %lf\n", timeused);
  }
  #endif

  printf("\n");
  integral /= ((double) N);
  integral *= alpha_inv*beta_inv;

  printf("Integral = %lf\n", integral);
  return 0;
}