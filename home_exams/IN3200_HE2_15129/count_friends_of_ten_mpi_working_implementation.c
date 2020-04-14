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

  /* Used to scatter v with MPI_Scatterv */
  int *sendcounts = malloc(comm_sz *sizeof *sendcounts);
  int *send_displs = malloc(comm_sz *sizeof *send_displs);
  send_displs[0] = 0;


  /* Necessary parameters to distribute rows */
  int rows = M/comm_sz;
  int row_remainder = (M % comm_sz);

  /* Compute n_rows, sendcounts, send_displs */
  for (int rank = 0; rank < comm_sz-1; rank++){
    n_rows[rank] = rows;
    sendcounts[rank] = n_rows[rank]*N;
    send_displs[rank+1] = send_displs[rank] + sendcounts[rank];
  }
  n_rows[comm_sz-1] = rows + row_remainder;
  sendcounts[comm_sz-1] = n_rows[comm_sz-1]*N;


  // Flatten matrix v
  int *v_flat;
  int *v_local = (int*)malloc(N*n_rows[my_rank] *sizeof *v_local);


  start = MPI_Wtime();
  if (my_rank == 0){
    v_flat = (int*)malloc(N*M*sizeof *v_flat);
    for (i = 0; i < M; i++){
      for (j = 0; j < N; j++){
        v_flat[i*N + j] = v[i][j];
      }
    }
  }
  end = MPI_Wtime();
  timeused = end-start;
  if (my_rank == 0) printf("Time used flattening array = %lf\n", timeused);


  // Scatter the data among the processes. Process comm_sz-1 gets the remainder
  MPI_Scatterv(v_flat, sendcounts, send_displs, MPI_INT, v_local, N*n_rows[my_rank], MPI_INT, 0, MPI_COMM_WORLD
  */

  /* Print the results to check the matrix is distributed correctly */
  /*
  MPI_Barrier(MPI_COMM_WORLD);
  if (my_rank == 0){
    printf("Process 0\n");
    for (i = 0; i < n_rows[my_rank]; i++){
      for (j = 0; j < N; j++){
        printf("%d ", v_local[i*N + j]);
      }
      printf("\n");
    }
    printf("---------------------------------------------------------\n");
  }

  MPI_Barrier(MPI_COMM_WORLD);
  if (my_rank == 1){
    printf("Process 1\n");
    for (i = 0; i < n_rows[my_rank]; i++){
      for (j = 0; j < N; j++){
        printf("%d ", v_local[i*N + j]);
      }
      printf("\n");
    }
    printf("---------------------------------------------------------\n");
  }
  */

  start = MPI_Wtime();
  for (i = 0; i < n_rows[my_rank]; i++){
    for (j = 0; j < N; j++){
      /* Check for friends of ten along row i */
      tmp = 0;
      for (k = 0; k < 3 && j < N-2; k++){
        tmp += v_local[i*N + j+k];
      }
      if (tmp == 10) num_triple_friends_local++;

      /* Check for friends of ten along column j */
      tmp = 0;
      for (k = 0; k < 3 && i < n_rows[my_rank]-2; k++){
        tmp += v_local[(i+k)*N + j];
      }
      if (tmp == 10) num_triple_friends_local++;

      /* Check for friends of ten along the diagonal (i,j), (i+1,j+1), (i+2, j+2) */
      tmp = 0;
      for (k = 0; k < 3 && i < n_rows[my_rank]-2 && j < N-2; k++){
        tmp += v_local[(i+k)*N + j+k];
      }
      if (tmp == 10) num_triple_friends_local++;

      /* Check for friends of ten along the diagonal (i,j), (i+1, j-1), (i+2, j-2) */
      tmp = 0;
      for (k = 0; k < 3 && i < n_rows[my_rank]-2 && j-k >= 0; k++){
        tmp += v_local[(i+k)*N + j-k];
      }
      if (tmp == 10) num_triple_friends_local++;
    }
  }
  /* Process 0 must clean up around the boundaries */
  int stride;
  if (my_rank == 0){
    for (int rank = 0; rank < comm_sz-1; rank++){
      stride = n_rows[rank];
      for (i = n_rows[rank]-2; i < n_rows[rank]; i++){
        for (j = 0; j < N; j++){
          // Check for triple friends in the remaining columns
          tmp = 0;
          for (k = 0; k < 3; k++){
            tmp += v[i+k + rank*stride][j];
          }
          if (tmp == 10) num_triple_friends_local++;

          //Check for triple friends along remaining positive diagonal
          tmp = 0;
          for (k = 0; k < 3; k++){
            tmp += v[i+k + rank*stride][j+k];
          }
          if (tmp == 10) num_triple_friends_local++;

          // Check for triple friends along remaining negative diagonal
          tmp = 0;
          for (k = 0; k < 3; k++){
            tmp += v[i+k + rank*stride][j-k];
          }
          if (tmp == 10) num_triple_friends_local++;
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

  /* Test of a serialized version with a flattened array*/
  /*
  int serial_triple_friends = 0;
  if (my_rank == 0){
    for (i = 0; i < M; i++){
      //printf("Working on row %d of %d\r", i, M);
      for (j = 0; j < N; j++){
        // Check for friends of ten along row i
        tmp = 0;
        for (k = 0; k < 3 && j < N-2; k++){
          tmp += v_flat[i*N + j+k];
        }
        if (tmp == 10) serial_triple_friends++;

        // Check for friends of ten along column j
        tmp = 0;
        for (k = 0; k < 3 && i < M-2; k++){
          tmp += v_flat[(i+k)*N + j];
        }
        if (tmp == 10) serial_triple_friends++;

        // Check for friends of ten along the diagonal (i,j), (i+1,j+1), (i+2, j+2)
        tmp = 0;
        for (k = 0; k < 3 && i < M-2 && j < N-2; k++){
          tmp += v_flat[(i+k)*N + j+k];
        }
        if (tmp == 10) serial_triple_friends++;

        // Check for friends of ten along the diagonal (i,j), (i+1, j-1), (i+2, j-2)
        tmp = 0;
        for (k = 0; k < 3 && i < M-2 && j-k >= 0; k++){
          tmp += v_flat[(i+k)*N + j-k];
        }
        if (tmp == 10) serial_triple_friends++;
      }
    }
    printf("Serial version gives = %d\n", serial_triple_friends);
  }
  */


  return num_triple_friends;
}
