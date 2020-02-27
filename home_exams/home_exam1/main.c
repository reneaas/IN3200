#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "read_graph_from_file1.h"


int main(int argc, char const *argv[]) {
  //char *filename = "8-webpages.txt";
  //char *filename = "web-NotreDame.txt";
  char *filename = argv[1];
  char **test_matrix;
  int N;
  read_graph_from_file1(filename, &N, &test_matrix);
  printf("Why tho? Print the damn matrix\n");
  printf("N = %d\n", N);

  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      printf("%d ", test_matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
