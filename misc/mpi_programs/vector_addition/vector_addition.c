#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
  int my_rank, comm_sz, n;
  int n_local;
  double *x_local, *y_local, *z_local;
  double *x = NULL, *y = NULL, *z = NULL;   //Initialize the pointers, otherwise a warning arises that they may be uninitialized.



  MPI_Init(NULL, NULL);       //Set up the MPI Universe
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);  //Tell the communicator the comunication size (number of processes) comm_sz.
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  //Assign rank to all the processes; ranks are assigned as 0, 1, ..., comm_sz - 1.

  //Process 0 takes input from the command line that is provided by the user.
  if (my_rank == 0){
    printf("Give length of vectors\n");
    scanf("%d", &n);
    x = (double*)malloc(n*sizeof(double));
    y = (double*)malloc(n*sizeof(double));
    z = (double*)malloc(n*sizeof(double));       //Result vector z = x + y.
    for (int i = 0; i < n; i++){
      x[i] = i;
      y[i] = i;
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);

  //Broadcast the length of the vectors to all processes.
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);   //Process 0 broadcasts n to all other processes.
  n_local = n/comm_sz;
  x_local = (double*)malloc(n_local*sizeof(double));
  y_local = (double*)malloc(n_local*sizeof(double));
  z_local = (double*)malloc(n_local*sizeof(double));
  //Scatter the data evenly among the processes using MPI_Scatter.
  MPI_Scatter(x, n_local, MPI_DOUBLE, x_local, n_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);   //x is divided evenly among all processes.
  MPI_Scatter(y, n_local, MPI_DOUBLE, y_local, n_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);   //y is divided evenely among all processes.

  //Now do vector addition locally:
  for (int i = 0; i < n_local; i++){
    z_local[i] = x_local[i] + y_local[i];
  }

  //Now gather the result in z in process 0.
  MPI_Gather(z_local, n_local, MPI_DOUBLE, z, n_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);  //Gather the result of z = x + y at process 0.

  //Print results.
  if (my_rank == 0){
    printf("x is:\n");
    for (int i = 0; i < n; i++){
      printf("x[%d] = %lf\n", i, x[i]);
    }
    printf("y is:\n");
    for (int i = 0; i < n; i++){
      printf("y[%d] = %lf\n", i, y[i]);
    }
    printf("The resulting vector is:\n");
    for (int i = 0; i < n; i++){
      printf("z[%d] = %lf\n", i, z[i]);
    }
  }

  MPI_Finalize();     //Close down the MPI Universe.
  return 0;
}
