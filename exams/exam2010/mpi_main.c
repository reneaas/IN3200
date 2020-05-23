#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include "functions.h"

int main(){
    double *a = NULL, norm;
    double start, end, timeused, max_time;
    int my_rank, N;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0){
      N = 3124000;
      a = malloc(N*sizeof *a);
      for (int i = 0; i < N; i++){
        a[i] = 0.0001*i;
      }
    }

    start = MPI_Wtime();
    norm = euclidean_norm(a, N);
    end = MPI_Wtime();
    timeused = end-start;
    MPI_Allreduce(&timeused, &max_time, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    if (my_rank == 0){
      printf("Time used = %lf\n", max_time);
      printf("Rank %d got norm = %lf\n", my_rank, norm);
      free(a);
    }


    MPI_Finalize();
    return 0;
}
