#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
Performance = min(Peak_performance, memory_bandwidth/code_balance).
This code computes the memory_bandwidth using the formula:
memory_bandwidth = Performance*code_balance.

In the for-loop below, the code_balance = 2 since we have 1 load and one store divided by 1 flop. Hence code_balance = (1 load + 1 store)/(1 flop).


*/

int main() {

  double P, code_balance;
  code_balance = 2.;
  int N = 100000;
  double s = 0.5;
  double FLOPS = (double) N;

  double *A, *B;
  A = (double*)calloc(N, sizeof(double));
  B = (double*)calloc(N, sizeof(double));

  for (int i = 0; i < N; i++)
  {
    B[i] = 2*i*i;
  }

  clock_t start, end;

  start = clock();

  int stride = 1;
  for (int i = 0; i < N; i+=stride)
  {
    A[i] = s*B[i];
  }
  end = clock();

  free(A);
  free(B);

  double timeused = (double) (end-start)/CLOCKS_PER_SEC;

  P = (double) FLOPS/timeused;

  double bs = P*8*code_balance;
  double n_bytes = (double) N*sizeof(double);
  double bandwidth = 2*n_bytes/timeused;

  printf("memory bandwidth = %lf Gbytes/sec\n", bs/1e9);
  printf("Performance = %lf Gflops/sec\n", P/1e9);
  printf("memory bandwidth = %lf Gbytes/sec (again)\n", bandwidth/1e9);



  return 0;
}
