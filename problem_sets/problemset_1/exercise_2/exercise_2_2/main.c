#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int main()
{
   
}

void smooth2D(double **v_old, double **v_new, int n, int m)
{
  const double c = 0.5;
  for (int i = 1; i < n-1; i++)
  {
    for (int j = 0; j < m-1; j++)
    {
      v_new[i][j] = v_old[i][j] + c*(v_old[i-1][j] + v_old[i][j-1] - 4*v_old[i][j] + v[i][j+1] + v[i+1][j]);
    }
  }
}
