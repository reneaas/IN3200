#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
  FILE *fp = fopen("temperatures_binary.bin" , "rb");
  double **data;
  int n = 100000;
  int m = 2;
  data = (double**)malloc(n*sizeof(double*));
  double timeused_binary, timeused_ascii;
  clock_t start, end;

  for (int i = 0; i < n; i++)
  {
    data[i] = (double*)malloc(m*sizeof(double));
  }


  /*
  Below the code reads data from a .txt file and from a .bin file.
  */

  start = clock();
  //Read data from file with n rows and m columns.
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      fscanf(fp, "%lf", &data[i][j]);
    }
  }

  end = clock();
  timeused_binary = (double) (end-start)/CLOCKS_PER_SEC;
  fclose(fp);

  fp = fopen("temperatures.txt", "r");
  start = clock();
  //Read data from file with n rows and m columns.
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      fscanf(fp, "%lf", &data[i][j]);
    }
  }
  end = clock();
  timeused_ascii = (double) (end-start)/CLOCKS_PER_SEC;

  printf("time used with binary = %lf\n", timeused_binary);
  printf("time used with ascii = %lf\n", timeused_ascii);

  fclose(fp);


  /*
  The part below writes the written data to a .txt file and to a binary file.
  */


  //Write data to file with .txt extension.
  fp = fopen("temperatures_write_now.txt", "w");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      fprintf(fp, "%lf", data[i][j]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);



  //Write data to a binary file.
  fp = fopen("temperatures_write.bin", "wb");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      fprintf(fp, "%lf", data[i][j]);
    }
  }
  fclose(fp);
  return 0;
}
