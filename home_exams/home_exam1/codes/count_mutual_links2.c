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
  int mutual_web_links, tmp, row_elems, mutual_links, total_mutual_web_linkages = 0;
  #if defined(_OPENMP)
  {
    #pragma omp parallel for private(tmp, row_elems, mutual_links) reduction(+:total_mutual_web_linkages)
    for (int i = 0; i < N; i++){
      tmp = row_ptr[i];         //Create a tmp to avoid unnecessary loads in the inner loop.
      row_elems = row_ptr[i+1] - tmp; //Compute row elements to avoid unnecessary loads in the inner loop.
      mutual_links = row_elems - 1;
      for (int j = 0; j < row_elems; j++){
        //Avoid race conditions using atomic.
        #pragma omp atomic
        num_involvements[col_idx[j+tmp]] += mutual_links; //We add the mutual web link contribution to col_idx[j + row_ptr[i]]. Each column is equally involved in a given row.
      }
      total_mutual_web_linkages += (mutual_links+1)*mutual_links;
    }
  }
  #else
  {
    for (int i = 0; i < N; i++){
      tmp = row_ptr[i];     //Create a tmp to avoid unnecessary loads in the inner loop.
      row_elems = row_ptr[i+1]-tmp;   //Compute row elements to avoid unnecessary loads in the inner loop.
      mutual_links = row_elems - 1;
      for (int j = 0; j < row_elems; j++){
        num_involvements[col_idx[j+tmp]] += mutual_links;    //We add the mutual web link contribution to col_idx[j+row_ptr[i]]. Each column is equally involved in a given row.
      }
      total_mutual_web_linkages += (mutual_links+1)*mutual_links;
    }
  }
  #endif

  return 0.5*total_mutual_web_linkages;
}
