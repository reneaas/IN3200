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

  //for (int i = 0; i < N+1; i++) printf("row_ptr[%d] = %d\n", i, row_ptr[i]);

  int row_elements, mutual_web_links;
  for (int i = 0; i < N; i++){
    row_elements = row_ptr[i+1]-row_ptr[i];
    mutual_web_links = row_elements - 1;
    for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
      num_involvements[col_idx[j]] += mutual_web_links; //We add the mutual web link contribution to col_idx[j]. Each column is equally involved in a given row.
      total_mutual_web_linkages += mutual_web_links;   //Counting mutual web links, though we count them twice to avoid any if-tests. Multiplied with 0.5 at the end.
    }
    //total_mutual_web_linkages += (mutual_web_links+1)*mutual_web_links;
  }



  //We counted each mutual web link twice, so we multiply with 0.5
  total_mutual_web_linkages *= 0.5;

  return total_mutual_web_linkages;
}
