#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define pi_const 3.14159265359

int main(int argc, char const *argv[]) {
  int M = 14;

  double *um = (double*)malloc((M+2)*sizeof(double));
  double *u = (double*)malloc((M+2)*sizeof(double));
  double *up = (double*)malloc((M+2)*sizeof(double));

  double x, dx = 1.0/(M+1);
  double t, dt = dx;
  double *tmp;
  int i;
  double pi = 2.0*pi_const;

  for (i = 0; i <= M+1; i++){
    x = i*dx;
    um[i] = sin(pi*x);
  }

  for (i = 1; i <= M; i++){
    u[i] = um[i] + 0.5*(um[i-1] -2*um[i] + um[i+1]);
  }
  u[0] = 0.;
  u[M+1] = 0.;

  t = dt;
  while (t < 1.0) {
    t += dt;
    for (i = 1; i <= M; i++){
      up[i] = um[i] + u[i-1] + u[i+1];
    }
    up[0] = 0.;
    up[M+1] = 0.;

    tmp = um;
    um = u;
    u = up;
    up = tmp;
  }

  for (int i = 0; i < M+2; i++){
   printf("u[%d] = %lf\n", i, u[i]);
  }





  return 0;
}
