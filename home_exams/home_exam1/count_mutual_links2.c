#include <stdio.h>
#include <stdlib.h>

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{

  int total_mutual_web_linkages = 0;
  /*
  int row_elements: keeps track of how many elements there are on each row in the matrix.
                    The point of this is that each node involved gets row_elements-1
                    involvements.
  int mutual_web_links: Used to logically distinguish it from row_elements.
                        It's just equal to row_elements-1.
  */
  int row_elements, mutual_web_links;
  for (int i = 0; i < N; i++){
    for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
      row_elements = row_ptr[i+1]-row_ptr[i];
      mutual_web_links = row_elements - 1;
      num_involvements[col_idx[j]] += mutual_web_links; //We add the mutual web link contribution to col_idx[j]. Each column is equally involved in a given row.
      total_mutual_web_linkages += mutual_web_links;   //Counting twice as many.
    }
  }

  //We count each mutual web link twice, so we divide by 2.
  total_mutual_web_linkages *= 0.5;

  return total_mutual_web_linkages;
}
