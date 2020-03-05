#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_graph_from_file2.h"
#include "count_mutual_links2.h"
#include "count_mutual_links2_omp.h"
#include "top_n_webpages.h"

int main(int argc, char *argv[]){

  int N, N_links;
  clock_t start, end;
  double timeused;
  //char *filename = "8-webpages.txt";
  //r *filename = "web-NotreDame.txt";
  char *filename = argv[1];


  printf("-------------------------------------------------------------------------\n");
  //This section tests read_graph_from_file2
  printf("-------------------------------------------------------------------------\n");
  printf("Testing read_graph_from_file2:\n");
  printf("-------------------------------------------------------------------------\n");
  int *row_ptr, *col_idx;
  start = clock();
  read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Timeused by read_graph_from_file2 = %lf seconds\n", timeused);


  //Test count_mutual_links2
  printf("-------------------------------------------------------------------------\n");
  printf("Testing count_mutual_links2:\n");
  printf("-------------------------------------------------------------------------\n");

  int *num_involvements = (int*)calloc(N, sizeof(int));
  int total_mutual_web_linkages;
  start = clock();
  total_mutual_web_linkages = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
  printf("Timeused by count_mutual_links2 = %lf seconds\n", timeused);


  //Test count_mutual_links2_omp
  printf("-------------------------------------------------------------------------\n");
  printf("Testing count_mutual_links2_omp:\n");
  printf("-------------------------------------------------------------------------\n");

  int *num_involvements_omp = (int*)calloc(N, sizeof(int));
  int total_mutual_web_linkages_omp;
  start = clock();
  total_mutual_web_linkages_omp = count_mutual_links2_omp(N, N_links, row_ptr, col_idx, num_involvements_omp);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Total mutual web linkages = %d\n", total_mutual_web_linkages_omp);
  printf("Timeused by count_mutual_links2 = %lf seconds\n", timeused);

  return 0;
}
