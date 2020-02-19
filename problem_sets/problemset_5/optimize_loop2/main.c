#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define pi 3.1415926


void foo(int, double**, double**, double*, double*, double*);
void foo_optimized(int, double**, double**, double*, double*, double*);
void foo_optimized2(int, double**, double**, double*, double*, double*);

int main(int argc, char const *argv[])
{
  int n;
  double **a, **b, *d, *e, *c;

  n = 25000;
  a = (double**)calloc(n, sizeof(double*));
  b = (double**)calloc(n, sizeof(double*));
  d = (double*)calloc(n, sizeof(double));
  e = (double*)calloc(n, sizeof(double));
  c = (double*)calloc(n, sizeof(double));

  for (int i = 0; i < n; i++)
  {
    a[i] = (double*)calloc(n, sizeof(double));
    b[i] = (double*)calloc(n, sizeof(double));
  }

  for (int i = 0; i < n; i++)
  {
    d[i] = i;
    e[i] = -2*i;
    for (int j = 0; j < n; j++)
    {
      b[i][j] = i*j + 2*i + j;
    }
  }


  double timeused, timeused_optimized, timeused_optimized2;
  clock_t start, end;

  start = clock();
  foo(n, a, b, c, d, e);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;

  start = clock();
  foo_optimized(n, a, b, c, d, e);
  end = clock();
  timeused_optimized = (double) (end-start)/CLOCKS_PER_SEC;


  start = clock();
  foo_optimized2(n, a, b, c, d, e);
  end = clock();
  timeused_optimized2 = (double) (end-start)/CLOCKS_PER_SEC;

  double speedup = timeused/timeused_optimized2;

  printf("time used before optimization = %lf\n", timeused);
  printf("time used after optimzation = %lf\n", timeused_optimized);
  printf("time used after optimization 2 = %lf\n", timeused_optimized2);
  printf("speedup = %lf times as fast \n ", speedup);

  return 0;
}


void foo(int n, double **a, double **b, double *c, double *d, double *e)
{
  int i, j;
  for (j = 0; j < n; j++)
  {
    for (i = 0; i < n; i++)
    {
      a[j][i] = b[j][i] + d[j]*e[i];
    }
  }

  for (i = 0; i < n; i++) c[i] = exp(i/n)+sin(3.1415926*i/n);
}



void foo_optimized(int n, double **a, double **b, double *c, double *d, double *e)
{
  double pi_div_n, n_div;
  int i,j;

  pi_div_n = pi/n;
  n_div = 1/n;
  int remainder = n % 4;


  //Moved the computation of the array c out of the double for-loop.
  for (i = 0; i < n; i++) c[i] = exp(i*n_div)+sin(i*pi_div_n);


  //Loop unrolling of the outer loop with rolling depth of 4.
  for (j = 0; j < n; j+=4)
  {
    for (i = 0; i < n; i++)
    {
      a[j][i] = b[j][i] + d[j]*e[i];
      a[j+1][i] = b[j+1][i] + d[j+1]*e[i];
      a[j+2][i] = b[j+2][i] + d[j+2]*e[i];
      a[j+3][i] = b[j+3][i] + d[j+3]*e[i];
    }
  }

  //Remainder loop
  for (j = n - remainder; j < n; j++)
  {
    for (i = 0; i < n; i++)
    {
      a[j][i] = b[j][i] + d[j]*e[i];
    }
  }
}


void foo_optimized2(int n, double **a, double **b, double *c, double *d, double *e)
{
  double tmp1, tmp2, tmp3;
  int remainder = n % 4;

  //Moved this part outta the double loop into a loop of its own to reduce the number of expensive function calls from n^2 to n for each.
  for (int i = 0; i < n; i++) c[i] = sin(pi*i/n) + exp(1.*i/n);

  //Loop unrolling of the inner-loop acquires more speedup than loop-unrolling of the outer loop due to contiguous memory allocation.
  for (int j = 0; j < n; j++)
  {
    for (int i = 0; i < n; i += 4)
    {
      a[j][i] = b[j][i] + d[j]*e[i];
      a[j][i+1] = b[j][i+1] + d[j]*e[i+1];
      a[j][i+2] = b[j][i+2] + d[j]*e[i+2];
      a[j][i+3] = b[j][i+3] + d[j]*e[i+3];
    }
  }

  //remainder loop:
  for (int j = 0; j < n; j++)
  {
    //tmp1 = d[j];
    for (int i = n-remainder; i < n; i++)
    {
      a[j][i] = b[j][i] + d[j]*e[i];
    }
  }
}
