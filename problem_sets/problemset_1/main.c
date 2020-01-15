#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
  FILE *file = fopen("data_file.txt", "r");
  int number;
  char line[100];
  int i = 0;
  while (fgets(line, 100, file) != NULL && i < 1)
  {
    printf("%s\n", line);
  }
  return 0;
}
