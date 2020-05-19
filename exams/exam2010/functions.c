#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include "functions.h"

double euclidean_norm(double *a, int n)
{
  int comm_sz, my_rank;
  double sum = 0, local_sum = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int *displs = malloc(comm_sz*sizeof *displs);
  int *sendcounts = malloc(comm_sz*sizeof *sendcounts);

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int local_n = n/comm_sz;
  int remainder = n % comm_sz;

  displs[0] = 0;
  for (int rank = 0; rank < comm_sz-1; rank++){
    sendcounts[rank] = local_n + (remainder > 0);
    displs[rank+1] = displs[rank] + sendcounts[rank];
    remainder--;
  }
  sendcounts[comm_sz-1] = local_n + (remainder > 0);

  double *local_a = malloc(sendcounts[my_rank]*sizeof *local_a);
  printf("Got here tho\n");
  MPI_Scatterv(a, sendcounts, displs, MPI_DOUBLE, local_a, sendcounts[my_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

  for (int i = 0; i < local_n; i++){
    local_sum += local_a[i]*local_a[i];
  }
  printf("Got here too.\n");
  MPI_Gather(&local_sum, 1, MPI_DOUBLE, &sum, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  sum = sqrt(sum);

  //free(local_a);
  return sum;
}
