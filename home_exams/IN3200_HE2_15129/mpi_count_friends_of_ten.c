#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <mpi.h>

int MPI_count_friends_of_ten(int M, int N, int** v)
{
  int comm_sz, my_rank;
  int num_triple_friends = 0, num_triple_friends_local = 0;
  int tmp, i, j, k;
  double start, end, timeused;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


  /* Broadcast M and N to all processes */
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

  /* Number of rows for each process */
  int *n_rows = malloc(comm_sz*sizeof *n_rows);

  /* Necessary parameters to distribute rows */
  int rows = M/comm_sz;
  int row_remainder = (M % comm_sz);

  //Distributed rows among the processes as evenly as possible
  for (int rank = 0; rank < comm_sz-1; rank++){
    if (row_remainder > 0){
      n_rows[rank] = rows + 1;
      row_remainder--;
    }
    else{
      n_rows[rank] = rows;
    }
  }
  //In case of any remainder rows left, the last process get's them.
  n_rows[comm_sz-1] = rows + row_remainder;

  printf("Rank %d got n_rows = %d\n", my_rank, n_rows[my_rank]);
  int **v_local = (int**)malloc(n_rows[my_rank]*sizeof(int*));
  for (i = 0; i < n_rows[my_rank]; i++) v_local[i] = (int*)malloc(N*sizeof(int));
  // Send the respective rows to each process
  if (my_rank == 0){
    int cum_rows = 0;
    for (int rank = 1; rank < comm_sz; rank++){
      cum_rows += n_rows[rank-1];
      //printf("Sending data to process %d\n", rank);
      for (i = 0; i < n_rows[rank]; i++){
        MPI_Send(v[cum_rows + i], N, MPI_INT, rank, rank, MPI_COMM_WORLD);
        //printf("Sucessfully sent to rank %d\n", rank);
      }
    }
    for (i = 0; i < n_rows[my_rank]; i++){
      for (j = 0; j < N; j++){
        v_local[i][j] = v[i][j];
      }
    }
  }
  else{
    for (i = 0; i < n_rows[my_rank]; i++){
      //printf("Process %d trying to receive data from process 0\n", my_rank);
      MPI_Recv(v_local[i], N, MPI_INT, 0, my_rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }
  //printf("rank %d finished receiving\n", my_rank);
  MPI_Barrier(MPI_COMM_WORLD);

  start = MPI_Wtime();

  for (i = 0; i < n_rows[my_rank]; i++){
    //printf("Working on row %d of %d\r", i, M);
    for (j = 0; j < N; j++){
      /* Check for friends of ten along row i */
      tmp = 0;
      for (k = 0; k < 3 && j < N-2; k++){
        tmp += v_local[i][j+k];
      }
      if (tmp == 10) num_triple_friends_local++;

      /* Check for friends of ten along column j */
      tmp = 0;
      for (k = 0; k < 3 && i < n_rows[my_rank]-2; k++){
        tmp += v_local[i+k][j];
      }
      if (tmp == 10) num_triple_friends_local++;

      /* Check for friends of ten along the diagonal (i,j), (i+1,j+1), (i+2, j+2) */
      tmp = 0;
      for (k = 0; k < 3 && i < n_rows[my_rank]-2 && j < N-2; k++){
        tmp += v_local[i+k][j+k];
      }
      if (tmp == 10) num_triple_friends_local++;

      /* Check for friends of ten along the diagonal (i,j), (i+1, j-1), (i+2, j-2) */
      tmp = 0;
      for (k = 0; k < 3 && i < n_rows[my_rank]-2 && j-k >= 0; k++){
        tmp += v_local[i+k][j-k];
      }
      if (tmp == 10) num_triple_friends_local++;
    }
  }


  // Process 0 must clean up around the boundaries
  int stride = 0;
  if (my_rank == 0){
    for (int rank = 0; rank < comm_sz-1; rank++){
      stride += n_rows[rank];
      if (n_rows[rank] >= 2){
        for (i = stride-2; i < stride; i++){
          for (j = 0; j < N; j++){
            // Check for triple friends in the remaining columns
            tmp = 0;
            for (k = 0; k < 3; k++){
              tmp += v[i+k][j];
            }
            if (tmp == 10) num_triple_friends_local++;

            //Check for triple friends along remaining positive diagonal
            tmp = 0;
            for (k = 0; k < 3; k++){
              tmp += v[i+k][j+k];
            }
            if (tmp == 10) num_triple_friends_local++;

            // Check for triple friends along remaining negative diagonal
            tmp = 0;
            for (k = 0; k < 3; k++){
              tmp += v[i+k][j-k];
            }
            if (tmp == 10) num_triple_friends_local++;
          }
        }
      }

      if (n_rows[rank] == 1){
        for (i = stride-1; i < stride; i++){
          for (j = 0; j < N; j++){
            // Check for triple friends in the remaining columns
            tmp = 0;
            for (k = 0; k < 3; k++){
              tmp += v[i+k][j];
            }
            if (tmp == 10) num_triple_friends_local++;

            //Check for triple friends along remaining positive diagonal
            tmp = 0;
            for (k = 0; k < 3; k++){
              tmp += v[i+k][j+k];
            }
            if (tmp == 10) num_triple_friends_local++;

            // Check for triple friends along remaining negative diagonal
            tmp = 0;
            for (k = 0; k < 3; k++){
              tmp += v[i+k][j-k];
            }
            if (tmp == 10) num_triple_friends_local++;
          }
        }
      }
    }
  }


  //Perform reduction of num_triple_friends and broadcast result to all processes
  MPI_Allreduce(&num_triple_friends_local, &num_triple_friends, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  end = MPI_Wtime();
  timeused = end-start;
  if (my_rank == 0){
    printf("Time of computation = %lf\n", timeused);
  }
  return num_triple_friends;
}
