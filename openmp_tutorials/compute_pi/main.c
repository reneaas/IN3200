#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int N, number_of_threads, N_local;
  double I, h, a, b;


  N = atoi(argv[1]);

  number_of_threads = atoi(argv[2]);
  omp_set_num_threads(number_of_threads);
  a = 0.;
  b = 1.;
  h = (b-a)/((double) N);
  N_local = N/number_of_threads;



  double start, end, timeused;


  start = omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    double a_local, b_local, I_local, interval_length, x;
    I_local = 0.;
    interval_length = (b-a)/((double) number_of_threads);

    a_local = a + (double) interval_length*id;
    b_local = a + (double) interval_length*(id + 1);

    for (int i = 0; i < N_local; i++)
    {
      x = a_local + (i+0.5)*h;
      I_local += 1.0/(1. + x*x);
    }
    I_local *= 4.*h;
    #pragma omp atomic
      I += I_local;
  }
  end = omp_get_wtime();
  timeused = end-start;
  printf("Integral = %lf\n", I);
  printf("timeused = %lf\n", timeused);


  I = 0.;
  start = omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int i;
    double x, I_local;
    I_local = 0.;
    for (i = id; i < N; i+=number_of_threads)   //Cyclic distribution of work.
    {
      x = a + (i+0.5)*h;
      I_local += 4./(1. + x*x);
    }
    I_local *= h;
    #pragma omp atomic
      I += I_local;
  }

  end = omp_get_wtime();
  timeused = end-start;
  printf("Integral = %lf\n", I);
  printf("timeused = %lf\n", timeused);

  I = 0.;
  double x;
  start = omp_get_wtime();
  #pragma omp parallel
  {
    double sum = 0.;
    #pragma omp for
      for (int i = 0; i < N; i++)
      {
        x = a + (i+0.5)*h;
        sum += 4./(1. + x*x);
      }
    #pragma omp atomic
      I += sum*h;
  }

  end = omp_get_wtime();
  timeused = end-start;
  printf("Integral = %lf\n", I);
  printf("timeused = %lf\n", timeused);

  I = 0.;
  start = omp_get_wtime();
  #pragma omp parallel for reduction(+:I) schedule(static,10000)
  for (int i = 0; i < N; i++)
  {
    x = a + (i+0.5)*h;
    I += 4./(1. + x*x);
  }
  I *= h;
  end = omp_get_wtime();
  timeused = end-start;
  printf("Integral = %lf\n", I);
  printf("timeused = %lf\n", timeused);


  return 0;
}
