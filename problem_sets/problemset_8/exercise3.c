#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void serial_odd_even(int, float*);
void parallel_odd_even(int, float*);

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]);
  double timeused_parallel, timeused_serial;
  double start, end;

  float *a;
  //a = (float*)malloc(n*sizeof(float));
  a = (float*)calloc(n, sizeof(float));

  for (int i = 0; i < n; i++) a[i] = n-i;
  a[3] = 7;
  a[5] = 1;

  for (int i = 0; i < n; i++) printf("a[%d] = %f\n", i, a[i]);
  printf("------------------------------------------------------------------\n");

  int swap_odd, swap_even;
  swap_odd = 0; swap_even = 0;
  int number_of_threads;
  start = omp_get_wtime();
  #pragma omp parallel
  {
    number_of_threads = omp_get_num_threads();
    int i, j;
    int r = n % 2;
    float tmp_larger, tmp_lower;
    for (i = 0; i < n; i++)
    {
      if (i % 2 != 0)
      {
        #pragma omp for reduction(+:swap_odd)
        for (j = 0; j <= (int) n/2-1 + r; j++)
        {            //tmp_lower = a[2*j+1];
          if (a[2*j] > a[2*j+1])
          {
            tmp_larger = a[2*j];
            a[2*j] = a[2*j+1];
            a[2*j+1] = tmp_larger;
            swap_odd = 1;
          }
        }
      }

      if (i % 2 == 0)
      {
        #pragma omp for reduction(+:swap_even)
        for (j = 1; j <= n/2-1 + r; j++)
        {
          if (a[2*j-1] > a[2*j])
          {
            tmp_larger = a[2*j-1];
            a[2*j-1] = a[2*j];
            a[2*j] = tmp_larger;
            swap_even = 1;
          }
        }
      }

      if (!swap_odd && !swap_even){
        printf("Broke the shit after i = %d\n", i);
        break;
      }

      #pragma omp barrier
      #pragma omp single
      {
        swap_even = 0; swap_odd = 0;
      }
    }
  }
  //serial_odd_even(n, a);
  end = omp_get_wtime();
  timeused_parallel = end-start;

  for (int i = 0; i < n; i++) a[i] = n-i;
  a[3] = 7;
  a[5] = 1;

  start = omp_get_wtime();
  serial_odd_even(n, a);
  end = omp_get_wtime();
  timeused_serial = end-start;


  for (int i = 0; i < n; i++) printf("a[%d] = %f\n", i, a[i]);

  printf("Number of threads = %d\n", number_of_threads);
  printf("timeused parallel = %lf\n", timeused_parallel);
  printf("timeused serial = %lf\n", timeused_serial);
  return 0;
}


void serial_odd_even(int n, float *a)
{
  int i, j;
  int r = n % 2;
  float tmp_larger, tmp_lower;
  int swaps;
  for (i = 0; i < n; i++)
  {
    if (i % 2 != 0)
    {
      for (j = 0; j <= (int) n/2-1 + r; j++)
      {            //tmp_lower = a[2*j+1];
        if (a[2*j] > a[2*j+1])
        {
          tmp_larger = a[2*j];
          a[2*j] = a[2*j+1];
          //tmp_lower = a[2*j+2];
          a[2*j+1] = tmp_larger;
          //a[2*j+1] = tmp_lower;
          swaps += 1;
        }
      }
    }

    if (i % 2 == 0)
    {
      for (j = 1; j <= n/2-1 + r; j++)
      {
        if (a[2*j-1] > a[2*j])
        {
          tmp_larger = a[2*j-1];
          //tmp_lower = a[2*j+1];
          a[2*j-1] = a[2*j];
          a[2*j] = tmp_larger;
          //a[2*j] = tmp_lower;
          swaps += 1;
        }
      }
    }
      if (swaps == 0 && i > 0){
        printf("Broke the shit after i = %d\n", i);
        break;
      }
    swaps = 0;
  }
}
