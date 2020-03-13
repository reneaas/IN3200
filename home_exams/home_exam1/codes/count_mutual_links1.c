#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
  /*
  int N: number of nodes.
  char **table2D: 2D link matrix.
  int *num_involvements: 1D array of length N to store number of involvements.
  */

  int total_mutual_web_linkages = 0;
  /*
  This algorithm is rather simple and does the following:
  For a chosen inbound web-page inbound1, we run over every other possible website larger than inbound1.
  Then we check whether both of these webpages link to an inbound webpage.
  If so, we count it for each inbound webpage and also add to the total webpage linkage count.
  */
  #if defined(_OPENMP)
  {
    #pragma omp parallel
    {
      int id, nthreads, thread_len, start_row, end_row, mutual_links;
      int i, j, k;

      id = omp_get_thread_num();
      nthreads = omp_get_num_threads();
      thread_len = N/nthreads;
      start_row = id*thread_len;
      end_row = start_row + thread_len;
      int *local_num_involvements = (int*)calloc(N, sizeof(int));

      //int* local_num_involvements = (int*)calloc(N, sizeof(int));
      for (int i = start_row; i < end_row; i++){
        for (int j = 0; j < N; j++){
          if (table2D[i][j] == 1){
            for (int k = j + 1; k < N; k++){
              if (table2D[i][k] == 1)
                  {
                    total_mutual_web_linkages++;
                    local_num_involvements[j]++;
                    local_num_involvements[k]++;
                  }
            }
          }
        }
      }

      #pragma omp critical
      {
        for (int i = 0; i < N; i++){
          num_involvements[i] += local_num_involvements[i];
        }
      }
    }
  }
  #else
  {
    int i, j, k;
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        if (table2D[i][j] == 1){
          for (k = j + 1; k < N; k++){
            if (table2D[i][k] == 1)
                {
                  total_mutual_web_linkages++;
                  num_involvements[j]++;
                  num_involvements[k]++;
                }
          }
        }
      }
    }
  }
  #endif


  return total_mutual_web_linkages;
}

/*
#pragma omp parallel for private(i, j, k) reduction(+:total_mutual_web_linkages)
for (i = 0; i < N; i++){
  for (j = 0; j < N; j++){
    if (table2D[i][j] == 1){
      for (k = j + 1; k < N; k++){
        if (table2D[i][k] == 1)
            {
              total_mutual_web_linkages++;
              num_involvements[j]++;
              num_involvements[k]++;
            }
      }
    }
  }
}
*/
