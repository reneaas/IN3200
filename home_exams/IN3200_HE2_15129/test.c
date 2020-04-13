#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <mpi.h>

int MPI_count_friends_of_ten(int M, int N, int** v)
{
  int comm_sz, my_rank;
  int num_triple_friends = 0, num_triple_friends_local = 0;
  int tmp, i, j, k;
  int **v_local;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  /* Broadcast M and N to all processes */
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

  /* Allocate memory for local arrays */
  v_local = (int**)malloc(M*sizeof(int*));
  for (i = 0; i < M; i++) v_local[i] = (int*)malloc(N*sizeof(int));

  /* Send the matrix elements from 0 to each process */
  if (my_rank == 0){
    for (int p = 1; p < comm_sz; p++){
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          MPI_Send(&v[i][j], 1, MPI_INT, p, 1, MPI_COMM_WORLD);
        }
      }
    }
  }
  /* Each process receives the matrix elements from process 0 */
  else{
    for (i = 0; i < M; i++){
      for (j = 0; j < N; j++){
        MPI_Recv(&v_local[i][j], 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
    }
  }


  /* If number number of processes is 2. */
  if (comm_sz == 2){
    if (my_rank == 0){
      for (i = 0; i < M; i++){
        printf("Working on row %d of %d\r", i, M);
        for (j = 0; j < N; j++){
          /* Check for friends of ten along row i */
          tmp = 0;
          for (k = 0; k < 3 && j < N-2; k++){
            tmp += v[i][j+k];
          }
          if (tmp == 10) num_triple_friends_local++;

          /* Check for friends of ten along column j */
          tmp = 0;
          for (k = 0; k < 3 && i < M-2; k++){
            tmp += v[i+k][j];
          }
          if (tmp == 10) num_triple_friends_local++;
        }
      }
    }

    if (my_rank == 1){
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          /* Check for friends of ten along the diagonal (i,j), (i+1,j+1), (i+2, j+2) */
          tmp = 0;
          for (k = 0; k < 3 && i < M-2 && j < N-2; k++){
            tmp += v_local[i+k][j+k];
          }
          if (tmp == 10) num_triple_friends_local++;

          /* Check for friends of ten along the diagonal (i,j), (i+1, j-1), (i+2, j-2) */
          tmp = 0;
          for (k = 0; k < 3 && i < M-2 && j-k >= 0; k++){
            tmp += v_local[i+k][j-k];
          }
          if (tmp == 10) num_triple_friends_local++;
        }
      }
    }
  }

  /* If number of processes is 4 */
  if (comm_sz == 4){
    if (my_rank == 0){
      printf("Working on row %d of %d\r", i, M);
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          /* Check for friends of ten along row i */
          tmp = 0;
          for (k = 0; k < 3 && j < N-2; k++){
            tmp += v[i][j+k];
          }
          if (tmp == 10) num_triple_friends_local++;
        }
      }
    }

    if (my_rank == 1){
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          /* Check for friends of ten along column j */
          tmp = 0;
          for (k = 0; k < 3 && i < M-2; k++){
            tmp += v_local[i+k][j];
          }
          if (tmp == 10) num_triple_friends_local++;
        }
      }
    }

    if (my_rank == 2){
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          /* Check for friends of ten along the diagonal (i,j), (i+1,j+1), (i+2, j+2) */
          tmp = 0;
          for (k = 0; k < 3 && i < M-2 && j < N-2; k++){
            tmp += v_local[i+k][j+k];
          }
          if (tmp == 10) num_triple_friends_local++;
        }
      }
    }

    if (my_rank == 3){
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          /* Check for friends of ten along the diagonal (i,j), (i+1, j-1), (i+2, j-2) */
          tmp = 0;
          for (k = 0; k < 3 && i < M-2 && j-k >= 0; k++){
            tmp += v_local[i+k][j-k];
          }
          if (tmp == 10) num_triple_friends_local++;
        }
      }
    }
  }

  /* Sum up the total number of triple friends of ten */
  MPI_Reduce(&num_triple_friends_local, &num_triple_friends, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  return num_triple_friends;
}
