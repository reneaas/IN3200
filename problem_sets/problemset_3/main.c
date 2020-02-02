#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif


double numerical_integration(double, double, int);

int main() {
  double x_min, x_max, integral;
  x_min = 0.;
  x_max = 1.;
  int slices = 10;
  const double pi = M_PI;


  while (slices < 10000)
  {
    integral = numerical_integration(x_min, x_max, slices);
    printf("%lf\n", integral);
    slices += 100;
  }
  printf("------------------------------------------------------------------------------\n");
  printf("%lf\n", pi);

  // counting cycles.
  int n_div = 100000;
  unsigned long long start = __rdtsc();
  double value = numerical_integration(0, 1, n_div);
  unsigned long long end = __rdtsc();

  double avg = (double)(end - start)/n_div;

  printf("Average number of cycles: %lf\n", avg);



  return 0;
}


double numerical_integration (double x_min, double x_max, int slices){
  double delta_x = (x_max-x_min)/slices;
  double x, sum = 0.0;
  for (int i=0; i<slices; i++)
    {
      x = x_min + (i+0.5)*delta_x;
      sum = sum + 4.0/(1.0+x*x);
    }
    return sum*delta_x;
  }
