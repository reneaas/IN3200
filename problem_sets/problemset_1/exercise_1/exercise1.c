#include <stdio.h>
//#include <stdlib.h>
#include <math.h>

int main() {
  int n = 2;
  int N = 1000;
  double sum = 1.;
  double denom = 0;

  while (n <= N){
    denom = pow(2, (double) n);
    if (n%2 == 0){
      sum -= 1./denom;
    }
    else{
      sum += 1./denom;
    }
    n += 1;
  }
  double analytical = 0.8;
  printf("Numerical value: %f \n ", sum);
  printf("Analytical value: %f \n", analytical);

  return 0;
}
