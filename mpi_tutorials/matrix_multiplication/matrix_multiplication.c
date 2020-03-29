#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
  int comm_sz, my_rank;

  int N, N_local;
  double *A = NULL, *x = NULL, *y = NULL;
  double *x_local, *y_local, **A_local;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0){
    printf("Give the dimension n:\n");
    scanf("%d", &N);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);  //Broadcast this value to all processes.

    x = (double*)calloc(N, sizeof(double));
    y = (double*)calloc(N, sizeof(double));
    A = (double*)calloc(N*N, sizeof(double));
    for (int i = 0; i < N*N; i++){
      A[i] = 1;
  }


  MPI_Barrier(MPI_COMM_WORLD);
  N_local = N/comm_sz;

  MPI_Scatter()




  MPI_Finalize();

  return 0;
}
