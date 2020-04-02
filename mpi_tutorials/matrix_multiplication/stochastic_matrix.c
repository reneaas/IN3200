#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
  double *x, *A, *y_local, *A_local, *y, tmp;
  int n, n_local, m_local, my_rank, comm_sz, max_iterations = 10;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  if (my_rank == 0) n = 4;
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  x = (double*)calloc(n,sizeof(double));
  y = (double*)calloc(n,sizeof(double));
  if (my_rank == 0){
    A = (double*)calloc(n*n,sizeof(double));
    printf("comm_sz = %d\n", comm_sz);
    //x = (double*)malloc(n*sizeof(double));
    A[2] = 0.5;
    A[n + 2] = 1;
    A[2*n] = 0.25;
    A[2*n + 1] = 0.25;
    A[2*n + 3] = 0.25;
    A[3*n + 2] = 0.5;
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < n*n; i++) printf("A[%d] = %lf\n", i, A[i]);
    printf("-----------------------------------------------------\n");
    x[1] = 1.0;
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  n_local = n/comm_sz;
  m_local = n*n/comm_sz;
  if (my_rank == 0) printf("n = %d\n", n_local);
  y_local = (double*)calloc(n_local, sizeof(double));
  A_local = (double*)calloc(m_local, sizeof(double));
  MPI_Scatter(A, m_local, MPI_DOUBLE, A_local, m_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  for (int l = 0; l < max_iterations; l++){
    for (int i = 0; i < n_local; i++){
      tmp = y_local[i];
      for (int j = 0; j < n; j++){
        tmp += A_local[i*n + j]*x[j];
      }
      y_local[i] = tmp;
    }
    MPI_Allgather(y_local, n_local, MPI_DOUBLE, x, n_local, MPI_DOUBLE, MPI_COMM_WORLD);
    free(y_local);
    y_local = (double*)calloc(n_local, sizeof(double));
    MPI_Barrier(MPI_COMM_WORLD);
  }

  if (my_rank == 0){
    for (int i = 0; i < n; i++){
      printf("x[%d] = %lf\n", i, x[i]);
    }
  }



  MPI_Finalize();

  return 0;
}
