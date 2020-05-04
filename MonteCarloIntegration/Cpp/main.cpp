#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <omp.h>
#include <random>

using namespace std;

int main(int argc, char const *argv[]) {
  int N = 10000000, max_int = 100000;
  double max_inv, x, y, alpha, beta, alpha_inv, beta_inv, integral = 0;
  double tmp1, tmp2;
  max_inv = 1.0/max_int;
  alpha = 1;
  beta = 0.5;
  alpha_inv = 1./alpha;
  beta_inv = 2;
  double start, end, timeused;
	srand(1);
  //srand(time(0)); //Set up random seed

  random_device rd;
  mt19937_64 gen(rd());
  uniform_real_distribution<double> RandomNumberGenerator(0,1);


  #ifdef _OPENMP
  {
    start = omp_get_wtime();
    #pragma omp parallel private(x,y,tmp1,tmp2)
    {
      #pragma omp for reduction(+:integral)
      for (int i = 0; i < N; i++){
        x = RandomNumberGenerator(gen);
        y = RandomNumberGenerator(gen);

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
    start = clock();
    for (int i = 0; i < N; i++){
      //printf("Iteration = %d of %d\r", iteration, N);
      x = RandomNumberGenerator(gen);
      y = RandomNumberGenerator(gen);

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
