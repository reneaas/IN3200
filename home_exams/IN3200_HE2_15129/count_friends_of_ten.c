#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int count_friends_of_ten(int M, int N, int ** v)
{
  int num_triple_friends = 0;
  int tmp, i, j, k;


  for (i = 0; i < M; i++){
    //printf("Working on row %d of %d\r", i, M);
    for (j = 0; j < N; j++){
      /* Check for friends of ten along row i */
      tmp = 0;
      for (k = 0; k < 3 && j < N-2; k++){
        tmp += v[i][j+k];
      }
      if (tmp == 10) num_triple_friends++;

      /* Check for friends of ten along column j */
      tmp = 0;
      for (k = 0; k < 3 && i < M-2; k++){
        tmp += v[i+k][j];
      }
      if (tmp == 10) num_triple_friends++;

      /* Check for friends of ten along the diagonal (i,j), (i+1,j+1), (i+2, j+2) */
      tmp = 0;
      for (k = 0; k < 3 && i < M-2 && j < N-2; k++){
        tmp += v[i+k][j+k];
      }
      if (tmp == 10) num_triple_friends++;

      /* Check for friends of ten along the diagonal (i,j), (i+1, j-1), (i+2, j-2) */
      tmp = 0;
      for (k = 0; k < 3 && i < M-2 && j-k >= 0; k++){
        tmp += v[i+k][j-k];
      }
      if (tmp == 10) num_triple_friends++;
    }
  }

  return num_triple_friends;
}
