#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

double f(double x, int n);

int main(int argc, char const *argv[]) {
  double s = 0;
  int terms = 12;
  int iterations = 100000;
  clock_t start, end;
  double timeused;
  double x = 0.5;
  start = clock();
  for (int i = 0; i < iterations; i++){
    for (int j = 0; j < iterations; j++){
      s += log(1-x);
    }
  }
  end = clock();
  s /= ((double)iterations*iterations);
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Result of library function, s = %lf\n", s);
  printf("Time used by library function = %lf\n", timeused);

  //Manual implementation
  start = clock();
  for (int i = 0; i < iterations; i++){
    for (int j = 0; j < iterations; j++){
      s += f(x, terms);
    }
  }
  end = clock();
  s /= ((double) iterations*iterations);
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Result of taylor expansion, s = %lf\n", s);
  printf("Time used by taylor expansion = %lf\n", timeused);
  return 0;
}


double f(double x, int n)
{
  //Computes ln(1-x) for a x on the interval (0,1) using n terms of its taylor expansion
  double s = 0, tmp = x;
  //#pragma omp parallel for reduction(+:s)
  for (int i = 1; i < n+1; i++, tmp*=x){
    s -= tmp/((double) i);
  }
  return s;
}
