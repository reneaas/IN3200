#include <stdio.h>
#include <stdlib.h>

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{
  /*
  int row_elements: keeps track of how many elements there are on each row in the matrix.
                    The point of this is that each node involved gets row_elements-1
                    involvements.
  int mutual_web_links: Used to logically distinguish it from row_elements.
                        It's just equal to row_elements-1.
  */

  int mutual_web_links, tmp, row_elems, total_mutual_web_linkages = 0;
  #if defined(_OPENMP)
  {
    #pragma omp parallel for private(tmp, row_elems) reduction(+:total_mutual_web_linkages)
    for (int i = 0; i < N; i++){
      tmp = row_ptr[i];         //Create a tmp to avoid unnecessary loads in the inner loop.
      row_elems = row_ptr[i+1] - tmp; //Compute row elements to avoid unnecessary loads in the inner loop.
      for (int j = 0; j < row_elems; j++){
        //Insert atomic to avoid race conditions when updating num_involvements.
        #pragma omp atomic
        num_involvements[col_idx[j+tmp]] += row_elems-1; //We add the mutual web link contribution to col_idx[j + row_ptr[i]]. Each column is equally involved in a given row.
      }
      total_mutual_web_linkages += (row_elems)*(row_elems-1);
    }
  }
  #else
  {
    for (int i = 0; i < N; i++){
      tmp = row_ptr[i];     //Create a tmp to avoid unnecessary loads in the inner loop.
      row_elems = row_ptr[i+1]-tmp;   //Compute row elements to avoid unnecessary loads in the inner loop.
      for (int j = 0; j < row_elems; j++){
        num_involvements[col_idx[j+tmp]] += row_elems-1;    //We add the mutual web link contribution to col_idx[j+row_ptr[i]]. Each column is equally involved in a given row.
      }
      total_mutual_web_linkages += (row_elems)*(row_elems-1);
    }
  }
  #endif

  return 0.5*total_mutual_web_linkages;
}
