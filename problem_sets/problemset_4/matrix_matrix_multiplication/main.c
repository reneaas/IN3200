#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char const *argv[]) {
  double **A, **B, **C;
  int n, m, p;
  clock_t start, end;
  double timeused, timeused_unrolling;

  n = 1000;
  m = 500;
  p = 350;

  A = (double**)calloc(n, sizeof(double*));
  B = (double**)calloc(m, sizeof(double*));
  C = (double**)calloc(n, sizeof(double*));

  for (int i = 0; i < n; i++) A[i] = (double*)calloc(m, sizeof(double));
  for (int i = 0; i < n; i++) C[i] = (double*)calloc(p, sizeof(double));

  for (int i = 0; i < m; i++)
  {
    B[i] = (double*)calloc(p, sizeof(double));
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      A[i][j] = i + j;
    }
  }

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < p; j++)
    {
      B[i][j] = i + j;
    }
  }

  start = clock();
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < p; j++)
    {
      for (int k = 0; k < m; k++)
      {
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  end = clock();

  timeused = (double) (end - start)/CLOCKS_PER_SEC;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < p; j++)
    {
      C[i][j] = 0.;
    }
  }

  //Loop unrolling:
  //Assuming a cache-line is 8 words (8 floating point numbers in this case).

  start = clock();
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < p; j+=4)
    {
      for (int k = 0; k < m; k++)
      {
        C[i][j] += A[i][k]*B[k][j];
        C[i][j+1] += A[i][k]*B[k][j+1];
        C[i][j+2] += A[i][k]*B[k][j+2];
        C[i][j+3] += A[i][k]*B[k][j+3];
        C[i][j+4] += A[i][k]*B[k][j+4];
      }
    }
  }

  //Since p might not be a multiple of 4, we must compute a remainder code.
  //Remainder code for (p % 4) > 0:
  for (int i = 0; i < n; i++)
  {
    for (int j = p - (p % 4); j < p; j+=8)
    {
      for (int k = 0; k < m; k++)
      {
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  end = clock();
  timeused_unrolling = (double) (end-start)/CLOCKS_PER_SEC;

  //Free up memory
  for (int i = 0; i < n; i++)
  {
    free(A[i]);
    free(C[i]);
  }
  for (int i = 0; i < m; i++) free(B[i]);
  free(A);
  free(B);
  free(C);


  //print time used by the different parts of the program.
  printf("timeused without unrolling = %lf\n", timeused);
  printf("timeused with unrolling = %lf\n", timeused_unrolling);
  return 0;
}
