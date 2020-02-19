#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>


/*
Computes the dot product of two vectors of length N using OpenMP.
*/

int main(int argc, char const *argv[]) {
  int N = atoi(argv[1]);
  int n = atoi(argv[2]);
  double *a, *b;
  double dotproduct = 0.;
  double start, end, timeused;
  int number_of_threads;

  a = (double*)malloc(N*sizeof(double));
  b = (double*)malloc(N*sizeof(double));



  for (int i = 0; i < N; i++)
  {
    a[i] = 1;
    b[i] = 1;
  }

  omp_set_num_threads(n);
  //Computes the dotproduct in parallel.
  start = omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    if (id == 0) number_of_threads = omp_get_num_threads();
    #pragma omp parallel for reduction(+:dotproduct)
    for (int i = 0; i < N; i++)
    {
      dotproduct += a[i]*b[i];
    }
  }
  end = omp_get_wtime();
  timeused = end-start;

  printf("Number of threads = %d\n", number_of_threads);
  printf("timeused = %lf\n", timeused);
  printf("dotproduct = %lf\n", dotproduct);
}
