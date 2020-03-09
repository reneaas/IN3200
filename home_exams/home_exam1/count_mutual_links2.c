#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
      tmp = row_ptr[i];
      row_elems = row_ptr[i+1] - tmp;
      for (int j = 0; j < row_elems; j++){
        num_involvements[col_idx[j+tmp]] += row_elems-1; //We add the mutual web link contribution to col_idx[j + row_ptr[i]]. Each column is equally involved in a given row.
        total_mutual_web_linkages += j;   //Counting mutual web links

      }
    }
  }
  #else
  {
    for (int i = 0; i < N; i++){
      tmp = row_ptr[i];
      row_elems = row_ptr[i+1]-tmp;
      for (int j = 0; j < row_elems; j++){
        num_involvements[col_idx[j+tmp]] += row_elems-1;    //We add the mutual web link contribution to col_idx[j+row_ptr[i]]. Each column is equally involved in a given row.
        total_mutual_web_linkages += j;   //Counting mutual web links
      }
    }
  }
  #endif

  return total_mutual_web_linkages;
}
