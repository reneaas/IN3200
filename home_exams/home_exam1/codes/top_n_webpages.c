#include <stdio.h>
#include <stdlib.h>


void top_n_webpages(int num_webpages, int *num_involvements, int n)
{
  int *webpage_number = (int*)calloc(num_webpages, sizeof(int));
  int top_webpage_count = 0;
  int max_value = -1;       //Since the lowest value of involvements a webpage carry is 0, I set it to -1 to guarantee it's lower than any other value.

  for (int i = 0; i < num_webpages; i++) webpage_number[i] = i;

  //Using shell sort but to sort num_involvements in descending order.
  int gap, i, j, tmp1, tmp2;
  for (gap = num_webpages/2; gap > 0; gap /= 2){
    for (i = gap; i < num_webpages; i++){
      tmp1 = num_involvements[i];
      tmp2 = webpage_number[i];
      for (j = i; j >= gap && num_involvements[j-gap] < tmp1; j -= gap){
        num_involvements[j] = num_involvements[j-gap];
        webpage_number[j] = webpage_number[j-gap];
      }
      num_involvements[j] = tmp1;
      webpage_number[j] = tmp2;
    }
  }


  printf("-------------------------------------------------------------------------\n");
  printf("Ranking                Involvements             Web page number\n");
  printf("-------------------------------------------------------------------------\n");
  for (int i = 0; i < n; i++){
    printf("%d                            %d                         %d\n", i+1, num_involvements[i], webpage_number[i]+1);
  }
  printf("-------------------------------------------------------------------------\n");

  free(webpage_number);
}
