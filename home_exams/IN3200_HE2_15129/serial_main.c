#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "time.h"

int main(int argc, char *argv[]) {

  int M, N, **v, max_rand, num_triple_friends;
  clock_t start, end;
  double timeused;
  M = 150;
  N = 170;
  max_rand = 10;
  v = (int**)malloc(M*sizeof(int*));
  for (int i = 0; i < M; i++) v[i] = (int*)malloc(N*sizeof(int));

  /* Randomly initialize the matrix */
  //srand(time(0));
  printf("Creating matrix...\n");
  srand(2);
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      v[i][j] = rand() % max_rand;
    }
  }

  printf("Entering function...\n");
  start = clock();
  num_triple_friends = count_friends_of_ten(M, N, v);
  end = clock();
  timeused = (double) (end-start)/CLOCKS_PER_SEC;
  printf("num_triple_friends = %d\n", num_triple_friends);
  printf("Time used = %lf\n", timeused);

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N;j++){
      printf("%d ", v[i][j]);
    }
    printf("\n");
  }

  FILE *fp = fopen("random_matrix.txt", "w");
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      fprintf("%d\n", v[i][j]);
    }
  }
  fclose(fp);

  return 0;
}
