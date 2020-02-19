#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char const *argv[]) {

  #pragma omp parallel
  {
  int ID = omp_get_thread_num();
  printf("Hello(%d)", ID);
  printf(" world(%d) \n", ID);
  }
  return 0;
}
