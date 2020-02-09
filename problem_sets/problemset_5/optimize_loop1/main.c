#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


void foo_modified(int, double**, double **, int *);
void foo_modified2(int, double**, double **, int *);
void foo (int , double **, double **, int *);

int main(int argc, char const *argv[])
{
  double **mat, **s;
  int N, *v;

  N = 10000;
  mat = (double**)calloc(N, sizeof(double*));
  s = (double**)calloc(N, sizeof(double*));
  v = (int*)calloc(N, sizeof(int));

  for (int i = 0; i < N; i++)
  {
    mat[i] = (double*)calloc(N, sizeof(double));
    s[i] = (double*)calloc(N, sizeof(double));
  }

  for (int i = 0; i < N; i++)
  {
    v[i] = i;
    for (int j = 0; j < N; j++)
      s[i][j] = 5*i - 2*j;
    }

  clock_t start, end;
  double timeused, timeused_modified1, timeused_modified2;

  start = clock();
  foo(N, mat, s, v);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;

  start = clock();
  foo_modified(N, mat, s, v);
  end = clock();
  timeused_modified1 = (double) (end-start)/CLOCKS_PER_SEC;


  start = clock();
  foo_modified2(N, mat, s, v);
  end = clock();
  timeused_modified2 = (double) (end - start)/CLOCKS_PER_SEC;


  for (int i = 0; i < N; i++)
  {
    free(mat[i]);
    free(s[i]);
  }
  free(mat);
  free(s);
  free(v);

  printf("time used with foo = %lf\n", timeused);
  printf("time used with foo_modified1 = %lf\n", timeused_modified1);
  printf("time used with foo_modified2 = %lf\n", timeused_modified2);



}


void foo_modified(int N, double **mat, double **s, int *v)
{
  int i,j;
  int remainder = N % 4;
  double *tmp = (double*)calloc(N, sizeof(double));

  for (int i = 0; i < N; i++) tmp[i] = -cos(2*v[i]%256);

  for (j=0; j<N; j++)
  {
    for (i=0; i<N; i+=4)
    {

      mat[j][i] = s[j][i]*tmp[i];
      mat[j][i+1] = s[j][i+1]*tmp[i+1];
      mat[j][i+2] = s[j][i+2]*tmp[i+2];
      mat[j][i+3] = s[j][i+3]*tmp[i+3];
    }
  }

  //remainder loop:
  for (j=0; j<N; j++)
  {
    for (i=N - remainder; i<N; i++)
    {
      mat[j][i] = s[j][i]*tmp[i];
    }
  }
}

void foo (int N, double **mat, double **s, int *v)
{
  int i,j;
  double val;

  for (j=0; j<N; j++)
  {
    for (i=0; i<N; i++)
    {
      val = 1.0*(v[j]%256);
      mat[i][j] = s[i][j]*(sin(val)*sin(val)-cos(val)*cos(val));
    }
  }
}

void foo_modified2(int N, double **mat, double **s, int *v)
{
  int i,j;
  int remainder = N % 4;
  double *tmp = (double*)calloc(N, sizeof(double));

  for (int i = 0; i < N; i++) tmp[i] = -cos(2*v[i]%256);

  for (j=0; j<N; j+=4)
  {
    for (i=0; i<N; i++)
    {

      mat[j][i] = s[j][i]*tmp[i];
      mat[j+1][i] = s[j+1][i]*tmp[i];
      mat[j+2][i] = s[j+2][i]*tmp[i];
      mat[j+3][i] = s[j+3][i]*tmp[i];
    }
  }

  //remainder loop:
  for (j = N - (N % 4); j < N; j++)
  {
    for (i = 0; i < N; i++)
    {
      mat[j][i] = s[j][i]*tmp[i];
    }
  }
}
