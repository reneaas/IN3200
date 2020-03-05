#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_graph_from_file1.h"
#include "count_mutual_links1.h"
#include "count_mutual_links1_omp.h"
#include "top_n_webpages.h"
#include <omp.h>

int main(int argc, char *argv[]) {

  int N, N_links;
  double start, end, timeused;
  //char *filename = "8-webpages.txt";
  //char *filename = "web-NotreDame.txt";
  char *filename = argv[1];

  //This section tests read_graph_from_file1
  printf("-------------------------------------------------------------------------\n");
  printf("Testing read_graph_from_file1:\n");
  printf("-------------------------------------------------------------------------\n");
  char **test_matrix;
  //Test of the function read_graph_from_file1
  start = omp_get_wtime();
  read_graph_from_file1(filename, &N, &test_matrix);
  end = omp_get_wtime();
  timeused = end-start;
  printf("Timeused by read_graph_from_file1 = %lf seconds\n", timeused);



  //Testing count_mutual_links1
  printf("-------------------------------------------------------------------------\n");
  printf("Testing count_mutual_links1:\n");
  printf("-------------------------------------------------------------------------\n");

  int *num_involvements = (int*)calloc(N, sizeof(int));
  int total_mutual_web_linkages;

  start = omp_get_wtime();
  total_mutual_web_linkages = count_mutual_links1(N, test_matrix, num_involvements);
  end = omp_get_wtime();
  timeused = end-start;
  //for (int i = 0; i < N; i++) printf("Webpage %d is involved = %d times\n", i+1, num_involvements[i]);
  printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
  printf("Timeused by count_mutual_links1 = %lf seconds\n", timeused);



  //Test the function count_mutual_links1_omp

  omp_set_num_threads(8);
  printf("-------------------------------------------------------------------------\n");
  printf("Testing count_mutual_links1_omp:\n");
  printf("-------------------------------------------------------------------------\n");

  int *num_involvements_omp = (int*)calloc(N, sizeof(int));
  int total_mutual_web_linkages_omp;

  start = omp_get_wtime();
  total_mutual_web_linkages_omp = count_mutual_links1_omp(N, test_matrix, num_involvements_omp);
  end = omp_get_wtime();
  timeused = end-start;
  //for (int i = 0; i < N; i++) printf("Webpage %d is involved = %d times\n", i+1, num_involvements[i]);
  printf("Total mutual web linkages = %d\n", total_mutual_web_linkages_omp);
  printf("Timeused by count_mutual_links1_omp = %lf seconds\n", timeused);

  return 0;
}
