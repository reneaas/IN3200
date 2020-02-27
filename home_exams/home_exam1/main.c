#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void read_graph_from_file1(char*, int*, char***);
void allocate(double**, int *);

int main(int argc, char const *argv[]) {

  int max_line_length = 128;
  //char *filename = "8-webpages.txt";
  char *filename = "web-NotreDame.txt";
  char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  FILE *fp = fopen(filename, "r");
  char *token1, *token2;
  const char *N_string;
  int parameters[2];
  const char *delimiter1 = "Nodes: ";
  const char *delimiter2 = "Edges: ";


  for (int i = 0; i < 3; i++){
    fgets(line_buffer, max_line_length, fp);
  }

  char buffer[1024];
  token1 = strtok(line_buffer, delimiter1);
  int iter, counter;
  iter = 0; counter = 0;
  while (token1 != NULL){
    strcpy(buffer, token1);
    if (isdigit(buffer[0]) != 0 && atoi(&buffer[0]) != 0)
    {
      parameters[counter] = atoi(&buffer[0]);
      counter++;
    }
    if (counter == 2) break;
    token1 = strtok(NULL, delimiter1);
  }



  /*
  //The line of interest is at line 3 so we read until we get the third line.
  for (int i = 0; i < 3; i++){
    fgets(line_buffer, max_line_length, fp);
  }
  //for (int i = 0; i < max_line_length; i++) line_buffer2[i] = line_buffer[i];
  token1 = strtok(&line_buffer[0], delimiter1);
  token2 = strtok(&line_buffer[1], delimiter2);
  int l = 0;
  int counter = 0;
  while (token1 != NULL)
  {
    //printf("%c\n", token1[l]);
    if (isdigit(token1[l]) != 0 && atoi(&token1[l]) != 0)
    {
      N_string = &token1[l];
      parameters[counter] = atoi(N_string);
      //printf("Number = %d\n", parameters[counter]);
      counter++;
    }
    if (counter == 1) break;       //Once two numbers are found, we break the loop.
    l++;
  }
  while (token2 != NULL)
  {
    //printf("%c\n", token1[l]);
    if (isdigit(token2[l]) != 0 && atoi(&token2[l]) != 0)
    {
      N_string = &token2[l];
      parameters[counter] = atoi(N_string);
      //printf("Number = %d\n", parameters[counter]);
      counter++;
    }
    if (counter == 2) break;       //Once two numbers are found, we break the loop.
    l++;
  }
  */
  int N = parameters[0];                //Number of nodes.
  int N_links = parameters[1];          //Number of links
  printf("Number of nodes = %d\n", N);
  printf("Number of edges = %d\n", N_links);

  //Here we're gonna fill the matrix with 0's and 1's.


  /*
  int n = 10;
  double *A;
  allocate(&A);



  for (int i = 0; i < 8; i++) printf("A[%d] = %lf\n", i, A[i]);

  */
  return 0;
}

void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
int max_line_length = 128;
  //char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  char line_buffer[max_line_length];
  FILE *fp = fopen(filename, "r");
  fgets(line_buffer, max_line_length, fp);
  printf(": %s\n", line_buffer);
}


void allocate(double **matrix2D, int *N)
{
  int n = 10;
  *matrix2D = (double*)malloc(n*sizeof(double*));
  for (int i = 0; i < n; i++) (*matrix2D)[i] = i;
}
