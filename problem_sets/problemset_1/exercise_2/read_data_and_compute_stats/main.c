#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


/*
Reads data from a file and computes statistics of the file.
*/

void find_statistics(double*, double**, int);

int main()
{

  //Read a double column file with 100 rows and 2 columns.
  FILE *fp = fopen("temperatures.txt", "r");
  double **numberarray;
  int n,m;
  n = 100;
  m = 2;

  //Allocate memory to store values in a matrix.
  numberarray = (double**)malloc(n*sizeof(double*));
  for (int i = 0; i < n; i++)
  {
    numberarray[i] = (double*)malloc(m*sizeof(double));
  }

  //Read values from the file fp.
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      fscanf(fp, "%lf", &numberarray[i][j]);
    }
  }


  /*
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      printf("%lf ", numberarray[i][j]);
    }
    printf("\n");
  }
  */

  double* stats = (double*)malloc(4*sizeof(double));
  find_statistics(stats, numberarray, n);

  printf("Average = %lf\n", stats[0]);
  printf("STD = %lf\n", stats[1]);
  printf("min_value = %lf\n", stats[2]);
  printf("max_value = %lf\n", stats[3]);


  return 0;
}

void find_statistics(double* stats, double** values, int n)
{
  //double* stats = (double*)malloc(4*sizeof(double));
  //Compute average
  double avg = 0.;
  for (int i = 0; i < n; i++)
  {
    avg += values[i][1];
  }
  avg /= (double) n;

  //Compute standard deviation
  double std = 0.;

  for (int i = 0; i < n; i++)
  {
    std += (values[i][1]-avg)*(values[i][1]-avg);
  }

  std /= (double) (n-1);
  std = sqrt(std);

  //Find max and min value of the array.
  double max_value = -2000;
  double min_value = 2000;
  for (int i = 0; i < n; i++)
  {
    if (max_value < values[i][1]) max_value = values[i][1];
    if (min_value > values[i][1]) min_value = values[i][1];
  }

  stats[0] = avg;
  stats[1] = std;
  stats[2] = min_value;
  stats[3] = max_value;
}
