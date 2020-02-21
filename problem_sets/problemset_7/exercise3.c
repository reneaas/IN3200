#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>


/*
Solves exercise 3 from week 7.
*/

void dense_mat_vec_parallel(int, int, double*, double*, double*);
void dense_mat_vec(int, int, double*, double*, double*);


int main(int argc, char const *argv[])
{
  int m, n;
  double *A, *x, *y;
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  double start, end, timeused;
  //omp_set_num_threads(4);     //specify number of threads.


  A = (double*)malloc(n*m*sizeof(double));
  x = (double*)malloc(m*sizeof(double));
  y = (double*)malloc(n*sizeof(double));

  //initialize values of the matrix A and the vectors x and y.
  for (int i = 0; i < m; i++) x[i] = 0.0;
  for (int i = 0; i < n*m; i++) A[i] = 1.0;
  for (int i = 0; i < n; i++) y[i] = 1.0;

  //Call the function dense_mat_vec:
  start = omp_get_wtime();
  dense_mat_vec_parallel(m, n, x, A, y);
  end = omp_get_wtime();
  timeused = end-start;

  //for (int i = 0; i < m; i++) printf("x[%d] = %lf\n", i, x[i]);
  printf("timeused on first implementation = %lf\n", timeused);

  //Reinitialize values of the matrix A and the vectors x and y.
  for (int i = 0; i < m; i++) x[i] = 0.0;
  for (int i = 0; i < n*m; i++) A[i] = 1.0;
  for (int i = 0; i < n; i++) y[i] = 1.0;

  start = omp_get_wtime();
  #pragma omp parallel
  {
    int id, num_threads, thread_length, start_m, end_m, local_m;
    double *x_local, *A_local;
    id = omp_get_thread_num();
    num_threads = omp_get_num_threads();
    thread_length = m/num_threads;
    start_m = id*thread_length;
    end_m = start_m + thread_length;
    local_m = end_m-start_m;
    x_local = &x[start_m];
    A_local = &A[start_m*n];
    dense_mat_vec(local_m, n, x_local, A_local, y);
  }
  end = omp_get_wtime();
  timeused = end-start;
  printf("timeused on second implementation = %lf\n", timeused);

  //for (int i = 0; i < m; i++) printf("x[%d] = %lf\n", i, x[i]);
}

void dense_mat_vec_parallel(int m, int n, double *x, double *A, double *y)
{
  #pragma omp parallel
  {
  if (omp_get_thread_num() == 0) printf("%d\n", omp_get_num_threads());
  int i, j;
  #pragma omp for
  for (i = 0; i < m; i++)
  {
    double tmp = 0.;
    for (j = 0; j < n; j++)
    {
      tmp += A[i*n+j]*y[j];
    }
    x[i] = tmp;
  }
}
}

void dense_mat_vec(int m, int n, double *x, double *A, double *y)
{
  int i, j;
  for (i = 0; i < m; i++)
  {
    double tmp = 0.;
    for (j = 0; j < n; j++)
    {
      tmp += A[i*n+j]*y[j];
    }
    x[i] = tmp;
    }
  }
