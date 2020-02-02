#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(){

  double ***v, ***u;
  int nx, ny, nz, iterations;
  nx = 100;
  ny = 100;
  nz = 100;
  iterations = 40;

  v = (double***)malloc(nx*sizeof(double**));
  u = (double***)malloc(nx*sizeof(double**));

  for (int i = 0; i < nx; i++)
  {
    v[i] = (double**)malloc(ny*sizeof(double*));
    u[i] = (double**)malloc(ny*sizeof(double*));
  }

  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
      v[i][j] = (double*)malloc(nz*sizeof(double));
      u[i][j] = (double*)malloc(nz*sizeof(double));
    }
  }

  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
      for (int k = 0; k < nz; k++)
      {
        v[i][j][k] = 2 + sin(i*j*k*M_PI/((nx-1)*(ny-1)*(nz-1)));
        u[i][j][k] = 0.;
      }
    }
  }


  for (int l = 0; l < iterations; l++)
  {
    for (int i = 1; i < nx-2; i++)
    {
      for (int j = 1; j < ny-2; j++)
      {
        for (int k = 1; k < nz-2; k++)
        {
          u[i][j][k] = v[i][j][k] + ( v[i-1][j][k] + v[i][j-1][k] + v[i][k][j-1] - 6*v[i][j][k] +
                        v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1])/6;
        }
      }
    }
    for (int i = 0; i < nx; i++)
    {
      for (int j = 0; j < ny; j++)
      {
        for (int k = 0; k < nz; k++)
        {
          v[i][j][k] = u[i][j][k];
        }
      }
    }

  }

  free(u);
  free(v);




  return 0;
}
