#include <stdio.h>
#include <stdlib.h>

void top_n_webpages(int num_webpages, int *num_involvements, int n)
{


  int *top_webpages = (int*)calloc(n, sizeof(int));
  int *webpage_number = (int*)calloc(n, sizeof(int));
  int top_webpage_count = 0;
  int max_value = -1;       //Since the lowest value of involvements a webpage carry is 0, I set it to -1 to guarantee it's lower than any other value.
  for (int i = 0; i < n; i++){
    max_value = -1;
    for (int j = 0; j < num_webpages; j++){
      if (num_involvements[j] > max_value){
         max_value = num_involvements[j];
         top_webpages[top_webpage_count] = max_value;
         webpage_number[top_webpage_count] = j;
      }
    }
    num_involvements[webpage_number[top_webpage_count]] = -1;     //This webpage is no longer interesting, so we remove it altogether by setting it to -1.
    top_webpage_count++;
  }
  printf("-------------------------------------------------------------------------\n");
  printf("Ranking                Involvements             Web page number\n");
  printf("-------------------------------------------------------------------------\n");
  for (int i = 0; i < n; i++){
    printf("%d                            %d                         %d\n", i+1, top_webpages[i], webpage_number[i]+1);
  }
  printf("-------------------------------------------------------------------------\n");

  free(top_webpages);
  free(webpage_number);
}
