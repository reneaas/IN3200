#include <stdio.h>
#include <stdlib.h>

int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
  /*
  int N: number of nodes.
  char **table2D: 2D link matrix.
  int *num_involvements: 1D array of length N to store number of involvements.
  */

  int total_mutual_web_linkages = 0;
  int outbound1, outbound2, inbound;

  /*
  This algorithm is rather simple and does the following:
  For a chosen inbound web-page inbound1, we run over every other possible website larger than inbound1.
  Then we check whether both of these webpages link to an inbound webpage.
  If so, we count it for each inbound webpage and also add to the total webpage linkage count.
  */
  for (outbound1 = 0; outbound1 < N; outbound1++){
    for (outbound2 = outbound1 + 1; outbound2 < N; outbound2++){
      for (inbound = 0; inbound < N; inbound++){
        if (outbound1 != outbound2 &&
            table2D[inbound][outbound1] == table2D[inbound][outbound2] &&
            table2D[inbound][outbound1] == 1)
            {
              total_mutual_web_linkages++;
              num_involvements[outbound1] += 1;
              num_involvements[outbound2] += 1;
            }
      }
    }
  }
  return total_mutual_web_linkages;
}
