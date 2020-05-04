#include <stdlib.h>
#include <stdio.h>

void f(int ptr);

int main(int argc, char const *argv[]) {
  int **p, *q = NULL;
  int N;
  q = &N;
  f(*q);
  printf("%d\n", N);
  return 0;
}


void f(int ptr)
{
  ptr = 100;
}
