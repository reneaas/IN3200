#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double f(double x, int n);

int main(int argc, char const *argv[]) {
  int max_iterations = 100000000;
  int n = 14;
  double s, x = 1;
  clock_t start, end;
  double timeused;
  start = clock();
  for (int i = 0; i < max_iterations; i++){
    for (int j = 0; j < max_iterations; j++){
      s = exp(x);
    }
  }
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Library function result = %lf\n", s);
  printf("Timeused by library function = %lf\n", timeused);


  start = clock();
  for (int i = 0; i < max_iterations; i++){
    for (int j = 0; j < max_iterations; j++){
      s = f(x,n);
    }
  }
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Result = %lf\n", s);
  printf("Timeused = %lf\n", timeused);


  return 0;
}

double f(double x, int n)
{
  //Computes n terms of the exponential function at x.
  double s = 1, tmp = 1;
  for (int i = 1; i < n+1; i++){
    tmp *= i;
    s += x/tmp;
    x *= x;
  }
  return s;
}
