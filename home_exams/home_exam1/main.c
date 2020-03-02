#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "read_graph_from_file1.h"
#include "read_graph_from_file2.h"


int main(int argc, char *argv[]) {

  int N, N_links;
  clock_t start, end;
  double timeused;
  char *filename = "8-webpages.txt";
  //char *filename = "web-NotreDame.txt";
  //char *filename = argv[1];



  /*
  //This section tests read_graph_from_file1
  printf("----------------------------------------------------------------\n");
  printf("Testing read_graph_from_file1:\n");
  printf("----------------------------------------------------------------\n");
  char **test_matrix;
  //Test of the function read_graph_from_file1
  start = clock();
  read_graph_from_file1(filename, &N, &test_matrix);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Timeused by read_graph_from_file1 = %lf seconds\n", timeused);



  //prints the matrix
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      printf("%d ", test_matrix[i][j]);
    }
    printf("\n");
  }
  */



  printf("----------------------------------------------------------------\n");
  //This section tests read_graph_from_file2
  printf("----------------------------------------------------------------\n");
  printf("Testing read_graph_from_file2:\n");
  printf("----------------------------------------------------------------\n");
  int *row_ptr, *col_idx;
  start = clock();
  read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;



  for (int i = 0; i < N+1; i++){
    printf("row_ptr[%d] = %d\n", i, row_ptr[i]);
  }
  printf("--------------------------------------------------------------\n");

  for (int i = 0; i < N_links; i++){
    printf("col_idx[%d] = %d\n", i, col_idx[i]);
  }
  printf("Timeused by read_graph_from_file2 = %lf seconds\n", timeused);



  /*

  char **matrix = (char**)calloc(N, sizeof(char*));
  for (int i = 0; i < N; i++) matrix[i] = (char*)calloc(N, sizeof(char));

  int col_count = 0;
  for (int i = 0; i < N; i++){
    for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
      matrix[i][col_idx[col_count]] = (char) 1;
      col_count++;
    }
  }

  printf("----------------------------------------------\n");


  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  */





  return 0;
}
