#include <stdio.h>
#include <stdlib.h>


void top_n_webpages_bubblesort(int num_webpages, int *num_involvements, int n)
{


  int *webpage_number = (int*)calloc(num_webpages, sizeof(int));
  int top_webpage_count = 0;
  int max_value = -1;       //Since the lowest value of involvements a webpage carry is 0, I set it to -1 to guarantee it's lower than any other value.

  for (int i = 0; i < num_webpages; i++) webpage_number[i] = i;


  int tmp;

  //bubblesort but only n times so the end of the array contains the n-largest values.
  for (int i = 0; i < n; i++){
    for (int j = 0; j < num_webpages-1-i; j++){
      if (num_involvements[j] > num_involvements[j+1]){
        tmp = num_involvements[j+1];
        num_involvements[j+1] = num_involvements[j];
        num_involvements[j] = tmp;

        tmp = webpage_number[j+1];
        webpage_number[j+1] = webpage_number[j];
        webpage_number[j] = tmp;
      }
    }
  }


  printf("-------------------------------------------------------------------------\n");
  printf("Ranking                Involvements             Web page number\n");
  printf("-------------------------------------------------------------------------\n");
  for (int i = num_webpages-1; i >= num_webpages-n; i--){
    printf("%d                            %d                         %d\n", i+1, num_involvements[i], webpage_number[i]+1);
  }
  printf("-------------------------------------------------------------------------\n");

  free(webpage_number);
}
