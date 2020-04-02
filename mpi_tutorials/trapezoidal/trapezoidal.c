#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void Get_data(int, int, double*, double*, int*);

int main(int argc, char const *argv[]) {
  int comm_sz;
  int my_rank;
  int n;
  double a, b;
  int n_local, a_local, b_local;
  double h;
  double I_local = 0, I_total = 0;
  double x;
  //printf("Why");

  //Set up MPI Universe
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //printf("Enter a b n");
  if (my_rank == 0){
    printf("Enter a,b and n\n");
    scanf("%lf %lf %d", &a, &b, &n);
  }
  MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  h = (double) (b-a)/((double) n);

  n_local = n/comm_sz;
  a_local = a + n_local*my_rank*h;
  b_local = a_local + n_local*h;
  x = a_local;

  I_local += 0.5*(1/( 1 + (double) a_local*a_local) + 1/( 1 + (double) b_local*b_local));
  for (int i = 0; i < n_local-1; i++){
    x = local_a + (i+1)*h;

    I_local += 1/(1 + x*x);
  }

  MPI_Reduce(&I_local, &I_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);



  if (my_rank == 0){
    I_total *= h;
    printf("Integral = %lf\n", I_total);
  }
  MPI_Finalize();

  return 0;
}
