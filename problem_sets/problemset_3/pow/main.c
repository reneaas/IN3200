#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main() {
  double tmp1, tmp2, tmp3, res;
  double x = 2;
  tmp1 = x;
  tmp2 = x;
  tmp3 = x;


  clock_t start, end;
  double timeused_mine, timeused_pow;

  start = clock();

  for (int i = 1; i < 64;  )
  {
    tmp1 = tmp1*tmp1;
  }

  for (int j = 1; j < 32; j *= 2)
  {
    tmp2 = tmp2*tmp2;
  }

  for (int k = 1; k < 4; k*=2)
  {
    tmp3 = tmp3*tmp3;
  }

  res = tmp1*tmp2*tmp3;
  end = clock();

  timeused_mine = (double) (end-start)/CLOCKS_PER_SEC;
  printf("2^100 = %lf\n", res);
  printf("timeused with self-made function = %lf\n", timeused_mine);
  start = clock();
  res = pow(2,100);
  printf("pow(2,100) = %lf\n", res);
  end = clock();
  timeused_pow = (double) (end-start)/CLOCKS_PER_SEC;
  printf("timeused with pow = %lf\n", timeused_pow);
  return 0;
}
