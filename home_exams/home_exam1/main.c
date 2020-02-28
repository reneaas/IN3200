#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "read_graph_from_file1.h"


int main(int argc, char *argv[]) {

  clock_t start, end;
  double timeused;
  char *filename = "8-webpages.txt";
  //char *filename = "web-NotreDame.txt";
  //char *filename = argv[1];
  char **test_matrix;
  int N;

  start = clock();
  read_graph_from_file1(filename, &N, &test_matrix);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("N = %d\n", N);


  /*
  Prints the matrix
  */

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      printf("%d ", test_matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}
