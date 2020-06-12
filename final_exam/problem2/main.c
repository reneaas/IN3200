#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

int main(int argc, char const *argv[]) {
  int N = (int) pow(2,30);
  double start, end, timeused;
  int i,j, sqrt_N;
  char *array = malloc(N);
  array[0] = array[1] = 0;
  start = omp_get_wtime();
  #pragma omp parallel for private(i)
  for (i=2; i<N; i++)
  array[i] = 1;
  // N is a predefined very large integer
  sqrt_N = (int)(sqrt(N)); // square root of N
  for (i=2; i<=sqrt_N; i++) {
    if (array[i]) {
      #pragma omp parallel for private(j)
      for (j=i*i; j<N; j+=i)
      array[j] = 0;
    }
  }
  end = omp_get_wtime();
  timeused = end-start;
  printf("Timeused = %lf\n", timeused);

  free (array);
  return 0;
}
