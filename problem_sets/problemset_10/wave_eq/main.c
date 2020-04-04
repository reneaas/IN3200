#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define pi_const 3.14159265359

int main(int argc, char const *argv[]) {
  int M;
  double *tmp;
  int i;
  double pi = 2.0*pi_const;
  double *um, *u, *up;
  FILE *fp;

  int comm_sz, my_rank;
  double *um_local, *u_local, *up_local;
  int M_local;

  /* Initiate MPI universe */
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0){
    printf("Give M. Make sure M + 2 is divisible with 4.\n");
    scanf("%d", &M);
  }
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  double x, dx = 1.0/((double) M+1);
  double t, dt = dx;

  M_local = (M+2)/comm_sz; //Local array lengths.

  /* allocation of local arrays */
  um_local = (double*)malloc((M_local)*sizeof(double));
  u_local = (double*)malloc((M_local)*sizeof(double));
  up_local = (double*)malloc((M_local)*sizeof(double));

  /* process 0 sets up allocates and defines the initial values of the arrays */
  if (my_rank == 0){
    um = (double*)malloc((M+2)*sizeof(double));
    u = (double*)malloc((M+2)*sizeof(double));
    up = (double*)malloc((M+2)*sizeof(double));
    for (i = 0; i <= M+1; i++){
      x = i*dx;
      um[i] = sin(pi*x);
    }

    for (i = 1; i <= M; i++){
      u[i] = um[i] + 0.5*(um[i-1] - 2*um[i] + um[i+1]);
    }
    u[0] = 0.;
    u[M+1] = 0.;
  }

  /* Scatter the arrays evenly among the processes */
  MPI_Scatter(um, M_local, MPI_DOUBLE, um_local, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Scatter(u, M_local, MPI_DOUBLE, u_local, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  for (t = dt; t <= 1.0; t+=dt){
    //t += dt;
    for (i = 1; i <= M_local-2; i++){
      up_local[i] = um_local[i] + u_local[i-1] + u_local[i+1];
    }

    /* Process 0 gathers up the finalized products for each iteration */
    MPI_Gather(um_local, M_local, MPI_DOUBLE, um, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(u_local, M_local, MPI_DOUBLE, u, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(up_local, M_local, MPI_DOUBLE, up, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Process 0 computes the values at local boundaries and shuffles the arrays */
    if (my_rank == 0){
      /* Update the boundaries between each process */
      int stride = M_local;
      for (int rank = 0; rank < comm_sz; rank++){
        up[rank*stride] = um[rank*stride] + u[rank*stride-1] + u[rank*stride+1];
        up[rank*stride-1] = um[rank*stride-1] + u[rank*stride-2] + u[rank*stride];
      }
      /* Set the global boundary conditions */
      up[0] = 0.;
      up[M+1] = 0.;

      /* Swap pointers */

      tmp = um;
      um = u;
      u = up;
      up = tmp;
    }

    /* Again process 0 scatter the data evenly among all processes and repeats the procedure above */
    MPI_Scatter(um, M_local, MPI_DOUBLE, um_local, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(u, M_local, MPI_DOUBLE, u_local, M_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  }


  /* Prints the final result */
  if (my_rank == 0){
    fp = fopen("results.txt", "w");

    for (int i = 0; i < M+2; i++){
      fprintf(fp, "%lf\n", u[i]);
     printf("u[%d] = %lf\n", i, u[i]);
    }
    fclose(fp);
  }


  MPI_Finalize();





  return 0;
}
