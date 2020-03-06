#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_graph_from_file1.h"
#include "count_mutual_links1.h"
#include "top_n_webpages.h"

int main(int argc, char *argv[]) {

  int N, N_links;
  clock_t start, end;
  double timeused;
  //char *filename = "8-webpages.txt";
  //char *filename = "web-NotreDame.txt";
  char *filename = argv[1];


  //This section tests read_graph_from_file1
  printf("-------------------------------------------------------------------------\n");
  printf("Testing read_graph_from_file1:\n");
  printf("-------------------------------------------------------------------------\n");
  char **test_matrix;
  //Test of the function read_graph_from_file1
  start = clock();
  read_graph_from_file1(filename, &N, &test_matrix);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Timeused by read_graph_from_file1 = %lf seconds\n", timeused);





  //Test the function count_mutual_links1
  printf("-------------------------------------------------------------------------\n");
  printf("Testing count_mutual_links1:\n");
  printf("-------------------------------------------------------------------------\n");

  int *num_involvements = (int*)calloc(N, sizeof(int));
  int total_mutual_web_linkages;

  start = clock();
  total_mutual_web_linkages = count_mutual_links1(N, test_matrix, num_involvements);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  //for (int i = 0; i < N; i++) printf("Webpage %d is involved = %d times\n", i+1, num_involvements[i]);
  printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
  printf("Timeused by count_mutual_links1 = %lf seconds\n", timeused);



  //Testing top_n_webpages
  int n = 8;
  printf("-------------------------------------------------------------------------\n");
  printf("Testing top_n_webpages:\n");
  start = clock();
  top_n_webpages(N, num_involvements, n);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("Timeused by top_n_webpages = %lf seconds\n", timeused);
  printf("-------------------------------------------------------------------------\n");



  return 0;
}
