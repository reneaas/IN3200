#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "time.h"
#include <mpi.h>

int main(int argc, char *argv[]) {

  int M = 0, N = 0, **v = NULL, max_rand, num_triple_friends;
  int rank;
  double start, end, timeused;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){
    M = 27000;
    N = 27000;
    max_rand = 10;
    v = (int**)malloc(M*sizeof(int*));
    for (int i = 0; i < M; i++) v[i] = (int*)malloc(N*sizeof(int));

    /* Randomly initialize the matrix */
    //srand(time(0));
    printf("Creating matrix...\n");
    srand(3);
    for (int i = 0; i < M; i++){
      for (int j = 0; j < N; j++){
        v[i][j] = rand() % max_rand;
      }
    }
  }

  if (rank == 0) printf("Entering function...\n");
  start = MPI_Wtime();
  num_triple_friends = MPI_count_friends_of_ten(M, N, v);
  end = MPI_Wtime();
  timeused = end-start;
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0){
    printf("Friends of ten = %d\n", num_triple_friends);
    printf("Time used = %lf\n", timeused);

    /*
    for (int i = 0; i < M; i++){
      for (int j = 0; j < N; j++){
        printf("%d ", v[i][j]);
      }
      printf("\n");
    }
    */
  }

  MPI_Finalize();
  return 0;
}
