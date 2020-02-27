#include <stdio.h>


void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
  int max_line_length = 128;
  //char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  char line_buffer[max_line_length];
  FILE *fp = fopen(filename, "r");
  fgets(fp, n, fp);
  printf(": %s\n", buff);
}
