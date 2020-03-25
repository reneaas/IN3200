#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/*
This function how many times nodes are involved as outbound in mutual web linkages.
These are stored in num_involvements of length N which stores one value for each node.
It also computes the total number of mutual linkages.
The function is split into two parts, one if OpenMP is used and one if not.

int N: number of nodes in webgraph.

char **table2D: hyperlink matrix representing the webgraph.

int *num_involvements: array to contain number of involvements of each node in the webgraph.
*/
int count_mutual_links1(int N, char **table2D, int *num_involvements)
{

  int total_mutual_web_linkages = 0;
  int i, j, k;
  #if defined(_OPENMP)
  {
    #pragma omp parallel private(i,j,k)
    {
      int counter;
      #pragma omp for reduction(+:total_mutual_web_linkages, num_involvements[:N])
      for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
          counter = 0;          //reset counter
          if (table2D[i][j] == 1){    //Only enter if the matrix element is 1.
            for (k = j+1; k < N; k++){
              num_involvements[k] += table2D[i][k];   //Increment num_involvements[k] with the matrix elements themselves (it's either 0 or 1 anyway).
              counter += table2D[i][k];               //Increment temporary counter to be added to num_involvements[j] in the j-dependent loop.
            }
            num_involvements[j] += counter;           //Increment here to avoid unnecessary loads and stores in the k-dependent loop.
            total_mutual_web_linkages += counter;     //Increment the total number of linkages.
          }
        }
      }
    }
  }
  #else
  {
    int counter;
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        counter = 0;
        if (table2D[i][j] == 1){        //Only sum the matrix elements on the remainder of the row if table2D[i][j] = 1.
          for (k = j+1; k < N; k++){
            counter += table2D[i][k];
            num_involvements[k] += table2D[i][k];
          }
          num_involvements[j] += counter;
          total_mutual_web_linkages += counter;
        }
      }
    }
  }
  #endif

  return total_mutual_web_linkages;
}
