#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
  int max_line_length = 128;
  char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  FILE *fp = fopen(filename, "r");
  char *token;
  const char *N_string;
  int parameters[2];
  const char *delimiter = "Nodes: ";

  //Read the first 3 lines of the file. We want the third one to extract the desired parameters.
  for (int i = 0; i < 3; i++){
    fgets(line_buffer, max_line_length, fp);
  }

  //Here we exctract the number of nodes and edges of the graph.
  char buffer[1024];
  token = strtok(line_buffer, delimiter);
  int iter, counter;
  iter = 0; counter = 0;
  while (token != NULL){
    strcpy(buffer, token);
    if (isdigit(buffer[0]) != 0 && atoi(&buffer[0]) != 0)
    {
      parameters[counter] = atoi(&buffer[0]);
      counter++;
    }
    if (counter == 2) break;
    token = strtok(NULL, delimiter);
  }

  free(line_buffer);

  *N = parameters[0];                //Number of nodes.
  int N_links = parameters[1];          //Number of links
  printf("Number of nodes = %d\n", *N);
  printf("Number of edges = %d\n", N_links);

  /*
  Now we're going to read the actual data in the file. But first we remove the 4th line
  since it doesn't contain any data.
  */
  fgets(line_buffer, max_line_length, fp);

  /*
  Now, the actual data in the file is arranged in N_links rows and 2 columns.
  We proceed to read this data now. But first we allocate an array so the data can be stored in it.
  It has to be a (N x N) - matrix.
  */

  //First we allocate the 2D-array.
  *table2D = (char**)calloc((*N), sizeof(char**));
  for (int i = 0; i < (*N); i++) (*table2D)[i] = (char*)calloc((*N), sizeof(char*));

  //Then we fill the 2D-array with the values in the file.
  int i, j;
  for (int k = 0; k < N_links; k++){
    fscanf(fp, "%d %d", &i, &j);
    (*table2D)[j][i] = (char) 1;
  }

  //To ensure that self-links are disabled, we set the diagonal elements to be zeroes.
  for (int j = 0; j < *N; j++) (*table2D)[j][j] = (char) 0;

  fclose(fp);




  /*
  Here's an alternative way to extract the parameters N = nodes and N_links = edges:

  int max_line_length = 128;
  char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  char tmp1;
  char *tmp2 = (char*)malloc(max_line_length*sizeof(char));
  char *tmp3 = (char*)malloc(max_line_length*sizeof(char));
  for (int i = 0; i < 2; i++){
    fgets(line_buffer, max_line_length, fp);
  }
  int N, N_links;
  fscanf(fp,  "%c %s %d %s %d", &tmp1, tmp2, &N, tmp3, &N_links);
  printf("Nodes = %d\n", N);
  printf("Edges = %d\n", N_links);

  free(tmp2); free(tmp3);

  */
}
