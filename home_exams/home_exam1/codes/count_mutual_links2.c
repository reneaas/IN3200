#include <stdio.h>
#include <stdlib.h>


/*
This function how many times nodes are involved as outbound in mutual web linkages.
These are stored in num_involvements of length N which stores one value for each node.
It also computes the total number of mutual linkages.
The function is split into two parts, one if OpenMP is used and one if not.
The parallelized version is simply using a #pragma omp parallel for with an atomic region
to avoid race conditions when updating num_involvements since all threads need access to the entire array.
*/
int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{
  int mutual_links, total_mutual_web_linkages = 0;
  #if defined(_OPENMP)
  {
    #pragma omp parallel for private(mutual_links) reduction(+:total_mutual_web_linkages, num_involvements[:N])
    for (int i = 0; i < N; i++){
      mutual_links = row_ptr[i+1]-row_ptr[i]-1;
      total_mutual_web_linkages += (mutual_links+1)*mutual_links;
      for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
        num_involvements[col_idx[j]] += mutual_links;    //We add the mutual web link contribution to col_idx[j]. Each column is equally involved in a given row.
      }
    }
  }
  #else
  {
    for (int i = 0; i < N; i++){
      mutual_links = row_ptr[i+1]-row_ptr[i]-1;
      total_mutual_web_linkages += (mutual_links+1)*mutual_links;
      for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
        num_involvements[col_idx[j]] += mutual_links;    //We add the mutual web link contribution to col_idx[j]. Each column is equally involved in a given row.
      }
    }



  }
  #endif

  return 0.5*total_mutual_web_linkages;
}


/*
#pragma omp parallel for private(mutual_links) reduction(+:total_mutual_web_linkages, num_involvements[:N])
for (int i = 0; i < N; i++){
  mutual_links = row_ptr[i+1]-row_ptr[i]-1;
  total_mutual_web_linkages += (mutual_links+1)*mutual_links;
  for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
    num_involvements[col_idx[j]] += mutual_links;    //We add the mutual web link contribution to col_idx[j+row_ptr[i]]. Each column is equally involved in a given row.
  }
}
*/
