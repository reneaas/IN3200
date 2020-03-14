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
  int i, j, k;
  /*
  This algorithm is rather simple and does the following:
  For a chosen inbound web-page inbound1, we run over every other possible website larger than inbound1.
  Then we check whether both of these webpages link to an inbound webpage.
  If so, we count it for each inbound webpage and also add to the total webpage linkage count.
  */
  #if defined(_OPENMP)
  {
    #pragma omp parallel for private(i,j,k) reduction(+:total_mutual_web_linkages)
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        if (table2D[i][j] == 1){      //Only check other elements on row is 1 if table2D[i][j] is 1.
          for (k = j + 1; k < N; k++){
            if (table2D[i][k] == 1)
                {
                  total_mutual_web_linkages++;
                  //Insertion of critical directive to avoid race conditions when updating num_involvements.
                  #pragma omp critical
                  {
                    num_involvements[j]++;
                    num_involvements[k]++;
                  }
                }
          }
        }
      }
    }
  }
  #else
  {
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
