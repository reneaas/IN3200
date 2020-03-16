#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/*
This function how many times nodes are involved as outbound in mutual web linkages.
These are stored in num_involvements of length N which stores one value for each node.
It also computes the total number of mutual linkages.
The function is split into two parts, one if OpenMP is used and one if not.
The parallelized version is simply using a #pragma omp parallel for with a critical region
to avoid race conditions when updating num_involvements since all threads need access to the entire array.
*/
int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
  int total_mutual_web_linkages = 0;
  int i, j, k;
  #if defined(_OPENMP)
  {
    #pragma omp parallel for private(i,j,k) reduction(+:total_mutual_web_linkages)
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        if (table2D[i][j] == 1){      //Only check other elements on row is 1 if table2D[i][j] is 1.
          for (k = j + 1; k < N; k++){
            if (table2D[i][k] == 1){
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
        if (table2D[i][j] == 1){        //Only check other elements on row is 1 if table2D[i][j] is 1.
          for (k = j + 1; k < N; k++){
            if (table2D[i][k] == 1){
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
