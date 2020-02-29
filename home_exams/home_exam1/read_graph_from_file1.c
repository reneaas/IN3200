#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
  int max_line_length = 128;
  char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  FILE *fp = fopen(filename, "r");
  int N_links;
  //Read the first 2 lines of the file. We want the third one to extract the desired parameters.
  for (int i = 0; i < 2; i++){
    fgets(line_buffer, max_line_length, fp);
  }

  //Here we exctract the number of nodes and edges of the graph.
  fscanf(fp,  "%*s %*s %d %*s %d", N, &N_links);
  printf("Nodes = %d\n", *N);
  printf("Edges = %d\n", N_links);

  /*
  Now we're going to read the actual data in the file. But first we remove the 3rd and 4th line
  since it doesn't contain any data.
  */
  fgets(line_buffer, max_line_length, fp);
  fgets(line_buffer, max_line_length, fp);
  free(line_buffer);        //The buffer has served its purpose.

  /*
  Now, the actual data in the file is arranged in N_links rows and 2 columns.
  We proceed to read this data now. But first we allocate an array so the data can be stored in it.
  It has to be a (Nodes x Nodes) - matrix.
  */

  //Allocates the 2D-array.
  *table2D = (char**)calloc((*N), sizeof(char**));
  for (int i = 0; i < (*N); i++) (*table2D)[i] = (char*)calloc((*N), sizeof(char*));

  //Fills the 2D-array with the values in the file.
  int FromNodeId, ToNodeId;
  for (int k = 0; k < N_links; k++){
    fscanf(fp, "%d %d", &FromNodeId, &ToNodeId);
    (*table2D)[ToNodeId][FromNodeId] = (char) 1;
  }

  //To ensure that self-links are disabled, we set the diagonal elements to be zeroes.
  for (int j = 0; j < *N; j++) (*table2D)[j][j] = (char) 0;

  fclose(fp);
}
