#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>


int main(int argc, char const *argv[]) {
  //int N = atoi(argv[1]);
  double x = 50;
  double *a, *b;
  int N = 10000;
  double tmp = 2*x;
  double start, end;
  //double timeused1, timeused2;
  double timeused1[5], timeused2[5];

  omp_set_num_threads(8);

  for (int k = 0; k < 5; k++)
  {

    //a = (double*)calloc(N, sizeof(double));
    //b = (double*)calloc(N, sizeof(double));
    a = (double*)malloc(N*sizeof(double));
    b = (double*)malloc(N*sizeof(double));

    for (int i = 0; i < N; i++)
    {
      a[i] = 0.;
      b[i] = 0.;
    }


    start = omp_get_wtime();
    #pragma omp parallel
    {
      int i,j;
      #pragma omp parallel for
      for (i = 0; i < N; i++)
      {
        a[i] = tmp;
      }
    }
    for (int i = 0; i < 10; i++) b[i] = tmp;
    end = omp_get_wtime();
    timeused1[k] = end-start;


    for (int i = 0; i < N; i++)
    {
      a[i] = 0.;
      b[i] = 0.;
    }




    start = omp_get_wtime();
    int number_of_threads;
    #pragma omp parallel
    {
      number_of_threads = omp_get_num_threads();
      int thread_length = N/number_of_threads;
      int id = omp_get_thread_num();
      double *a_local, *b_local;
      a_local = (double*)calloc(thread_length, sizeof(double));
      b_local = (double*)calloc(thread_length, sizeof(double));

      int start, end;
      start = id*thread_length;
      end = start + thread_length;

      int i, j;
      for (i = 0, j = start; i < thread_length, j < end; i++, j++)
      {
        a_local[i] = tmp;
        if (j < 10) b_local[i] = a_local[i];
      }

      for (i = 0, j = start; i < thread_length, j < end; i++, j++)
      {
          a[j] = a_local[i];
          b[j] = b_local[i];
      }

    }
    end = omp_get_wtime();
    timeused2[k] = end-start;
    N *= 10;
  }

  N = 10000;
  //for (int i = 0; i < N; i++) printf("b[%d] = %lf\n", i, b[i]);
  printf("N               First implementation       Second implementation\n");
  for (int i = 0; i < 5; i++)
  {
    printf("%d              %lf                   %lf\n", N, timeused1[i], timeused2[i]);
    N *= 10;
  }

  /*
  printf("Timeused1 = %lf\n", timeused1);
  printf("Timeused2 = %lf\n", timeused2);
  */




  return 0;
}
