#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
{
  int max_line_length = 128;
  char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  FILE *fp = fopen(filename, "r");

  //Read the first 2 lines of the file. We want the third one to extract the desired parameters.
  for (int i = 0; i < 2; i++){
    fgets(line_buffer, max_line_length, fp);
  }

  //Here we exctract the number of nodes and edges of the graph.
  fscanf(fp,  "%*s %*s %d %*s %d", N, N_links);
  printf("Nodes = %d\n", *N);
  printf("Edges = %d\n", *N_links);

  /*
  Now we're going to read the actual data in the file. But first we remove the 3rd and 4th line
  since it doesn't contain any data.
  */
  fgets(line_buffer, max_line_length, fp);
  fgets(line_buffer, max_line_length, fp);
  free(line_buffer);        //The buffer has served its purpose.

  //Allocate arrays for CRS storage scheme.
  *row_ptr = (int*)calloc(*N+1, sizeof(int*));
  *col_idx = (int*)calloc(*N_links, sizeof(int*));
  int *tmp_row = (int*)calloc(*N_links, sizeof(int));
  int *tmp_col = (int*)calloc(*N_links, sizeof(int));
  int *row_count = (int*)calloc(*N, sizeof(int));

  int FromNodeId, ToNodeId;
  for (int k = 0; k < *N_links; k++){
    fscanf(fp, "%d %d", &FromNodeId, &ToNodeId);
    tmp_col[k] = FromNodeId;
    tmp_row[k] = ToNodeId;
  }
  fclose(fp);

  printf("Finished reading the file, now we sort:\n");

  /*
  Here we sort the column array and count how many elements are on each row in the
  sparse matrix.
  */
  int x = 0;
  for (int i = 0; i < *N; i++){
    printf("Sorting for row %d of %d\n", i, *N);
    for (int j = 0; j < *N_links; j++){
      if (tmp_row[j] == i && tmp_row[j] != tmp_col[j]){
        (*col_idx)[x] = tmp_col[j];
        row_count[i] += 1;
        x++;
      }
    }
  }
  //The temporary arrays for the row and column elements have served their purpose.
  free(tmp_row);
  free(tmp_col);

  //Fills the row pointer.
  int row_elems = 0;
  for (int i = 1; i < *N+1; i++){
    row_elems += row_count[i-1];
    (*row_ptr)[i] = row_elems;
  }

  free(row_count);      //Free up memory.
}
