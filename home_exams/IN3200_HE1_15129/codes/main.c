#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <omp.h>

int main(int argc, char *argv[]){

  int N, N_links;                     //N is number of nodes and N_links is number of edges in the webgraphs.
  double timeused;
  char *filename1 = argv[1];          //File that will be read by read_graph_from_file1
  char *filename2 = argv[2];          //File that will be read by read_graph_from_file2

  #if defined(_OPENMP)
  {
    double start, end;

    //This section tests read_graph_from_file1
    printf("-------------------------------------------------------------------------\n");
    printf("Testing read_graph_from_file1:\n");
    printf("-------------------------------------------------------------------------\n");
    char **hyperlink_matrix;       //
    //Test of the function read_graph_from_file1
    start = omp_get_wtime();
    read_graph_from_file1(filename1, &N, &hyperlink_matrix);
    end = omp_get_wtime();
    timeused = end-start;
    printf("Timeused by read_graph_from_file1 = %lf seconds\n", timeused);

    //Test the function count_mutual_links1
    printf("-------------------------------------------------------------------------\n");
    printf("Testing count_mutual_links1 (parallelized with OpenMP):\n");
    printf("-------------------------------------------------------------------------\n");
    FILE *fp = fopen("count_mutual_links1_parallel_results.txt", "w");
    fprintf(fp, "Timeused                Threads\n");
    int *num_involvements;
    int total_mutual_web_linkages;
    for (int num_threads = 1; num_threads <= 1024; num_threads *= 2){
      omp_set_num_threads(num_threads);       //Tells OpenMP how many threads to fork.
      num_involvements = (int*)calloc(N, sizeof(int));    //Allocate memory
      total_mutual_web_linkages = 0;
      start = omp_get_wtime();
      total_mutual_web_linkages = count_mutual_links1(N, hyperlink_matrix, num_involvements);
      end = omp_get_wtime();
      timeused = end-start;
      printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
      printf("Timeused by count_mutual_links1 = %lf seconds\n", timeused);
      fprintf(fp ,"%lf          %d\n", timeused, num_threads);      //Write data to file.
      top_n_webpages(N, num_involvements, (int) 10);    //Prints the top 10 webpages each time to check for race condition problems.
      free(num_involvements);
    }
    fclose(fp);
    num_involvements = (int*)calloc(N, sizeof(int));
    omp_set_num_threads(8);
    total_mutual_web_linkages = count_mutual_links1(N, hyperlink_matrix, num_involvements);      //Here we just fill the array one more time.

    //Testing top_n_webpages
    int n = 10;
    printf("-------------------------------------------------------------------------\n");
    printf("Testing top_n_webpages:\n");
    start = omp_get_wtime();
    top_n_webpages(N, num_involvements, n);
    end = omp_get_wtime();
    timeused = end-start;
    printf("Timeused by top_n_webpages = %lf seconds\n", timeused);
    printf("-------------------------------------------------------------------------\n");
    free(num_involvements);

    for (int i = 0; i < N; i++) free(hyperlink_matrix[i]);
    free(hyperlink_matrix);


    //From here on out we test the CRS format functions of the project.
    N = 0;
    N_links = 0;
    //This section tests read_graph_from_file2
    printf("-------------------------------------------------------------------------\n");
    printf("Testing read_graph_from_file2:\n");
    printf("-------------------------------------------------------------------------\n");
    int *row_ptr, *col_idx;
    start = omp_get_wtime();
    read_graph_from_file2(filename2, &N, &N_links, &row_ptr, &col_idx);
    end = omp_get_wtime();
    timeused = end-start;
    printf("Timeused by read_graph_from_file2 = %lf seconds\n", timeused);


    printf("-------------------------------------------------------------------------\n");
    printf("Testing count_mutual_links2 (parallelized with OpenMP):\n");
    printf("-------------------------------------------------------------------------\n");

    fp = fopen("count_mutual_links2_parallel_results.txt", "w");
    fprintf(fp, "Timeused                Threads\n");
    for (int num_threads = 1; num_threads <= 32; num_threads *= 2){
      omp_set_num_threads(num_threads);
      num_involvements = (int*)calloc(N, sizeof(int)); //reset values
      total_mutual_web_linkages = 0;      //reset values.
      start = omp_get_wtime();
      total_mutual_web_linkages = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
      end = omp_get_wtime();
      timeused = end-start;
      printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
      printf("Timeused by count_mutual_links2 = %lf seconds\n", timeused);
      fprintf(fp, "%lf              %d\n", timeused, num_threads);
      top_n_webpages(N, num_involvements, (int) 10);
    }
    free(num_involvements);
    fclose(fp);
    num_involvements = (int*)calloc(N, sizeof(int));
    omp_set_num_threads(4);
    total_mutual_web_linkages = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

    //testing top_n_webpages
    n = 10;
    printf("-------------------------------------------------------------------------\n");
    printf("Testing top_n_webpages:\n");
    start = omp_get_wtime();
    top_n_webpages(N, num_involvements, n);
    end = omp_get_wtime();
    timeused = end-start;
    printf("Timeused by top_n_webpages = %lf seconds\n", timeused);
    free(num_involvements);
    free(row_ptr);
    free(col_idx);
  }
  #else
  {
    clock_t start, end;

    FILE *fp = fopen("serial_times.txt", "w");
    fprintf(fp, "Function name                      Timeused [s]\n");

    //This section tests read_graph_from_file1
    printf("-------------------------------------------------------------------------\n");
    printf("Testing read_graph_from_file1:\n");
    printf("-------------------------------------------------------------------------\n");
    char **hyperlink_matrix;
    //Test of the function read_graph_from_file1
    start = clock();
    read_graph_from_file1(filename1, &N, &hyperlink_matrix);
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused by read_graph_from_file1 = %lf seconds\n", timeused);
    fprintf(fp, "read_graph_from_file1                %lf\n", timeused);

    //Test the function count_mutual_links1
    printf("-------------------------------------------------------------------------\n");
    printf("Testing count_mutual_links1:\n");
    printf("-------------------------------------------------------------------------\n");
    int *num_involvements;
    int total_mutual_web_linkages;
    num_involvements = (int*)calloc(N, sizeof(int));
    total_mutual_web_linkages = 0;
    start = clock();
    total_mutual_web_linkages = count_mutual_links1(N, hyperlink_matrix, num_involvements);
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    //for (int i = 0; i < N; i++) printf("Webpage %d is involved = %d times\n", i+1, num_involvements[i]);
    printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
    printf("Timeused by count_mutual_links1 = %lf seconds\n", timeused);
    fprintf(fp ,"count_mutual_links1              %lf\n", timeused);

    //Testing top_n_webpages
    int n = 10;
    printf("-------------------------------------------------------------------------\n");
    printf("Testing top_n_webpages:\n");
    start = clock();
    top_n_webpages(N, num_involvements, n);
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused by top_n_webpages = %lf seconds\n", timeused);
    printf("-------------------------------------------------------------------------\n");
    free(num_involvements);

    N = 0;
    N_links = 0;
    //This section tests read_graph_from_file2
    printf("-------------------------------------------------------------------------\n");
    printf("Testing read_graph_from_file2:\n");
    printf("-------------------------------------------------------------------------\n");
    int *row_ptr, *col_idx;
    start = clock();
    read_graph_from_file2(filename2, &N, &N_links, &row_ptr, &col_idx);
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused by read_graph_from_file2 = %lf seconds\n", timeused);
    fprintf(fp, "read_graph_from_file2                %lf\n", timeused);


    printf("-------------------------------------------------------------------------\n");
    printf("Testing count_mutual_links2:\n");
    printf("-------------------------------------------------------------------------\n");

    num_involvements = (int*)calloc(N, sizeof(int)); //reset values
    total_mutual_web_linkages = 0;      //reset values.
    start = clock();
    total_mutual_web_linkages = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Total mutual web linkages = %d\n", total_mutual_web_linkages);
    printf("Timeused by count_mutual_links2 = %lf seconds\n", timeused);
    fprintf(fp, "count_mutual_links2                  %lf\n", timeused);

    free(row_ptr);
    free(col_idx);

    //testing top_n_webpages
    n = 10;
    printf("-------------------------------------------------------------------------\n");
    printf("Testing top_n_webpages:\n");
    start = clock();
    top_n_webpages(N, num_involvements, n);
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused by top_n_webpages = %lf seconds\n", timeused);
    fprintf(fp, "top_n_webpages                 %lf\n", timeused);
    fclose(fp);

    free(num_involvements); //Free up memory.
  }
  #endif

  return 0;
}
