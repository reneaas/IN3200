#include <stdio.h>
#include <stdlib.h>

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

  //Allocate temporary arrays
  int *tmp_row = (int*)calloc(*N_links, sizeof(int));
  int *tmp_col = (int*)calloc(*N_links, sizeof(int));

  int FromNodeId, ToNodeId, self_link_counter;
  self_link_counter = 0;
  int l = 0;
  for (int k = 0; k < *N_links; k++){
    fscanf(fp, "%d %d", &FromNodeId, &ToNodeId);
    if (FromNodeId != ToNodeId){
      tmp_col[l] = FromNodeId;
      tmp_row[l] = ToNodeId;
      l++;
    }
    else{
      self_link_counter++;
    }
  }
  fclose(fp);
  *N_links = *N_links - self_link_counter;
  printf("N_links after self link removal = %d\n", *N_links);

  printf("Finished reading the file, now we sort:\n");

  /*
  Here we sort the column array and count how many elements are on each row in the
  sparse matrix. This part needs to remove self-links also. That is when tmp_row[j] = tmp_col[j].
  This will necessarily create shorter column pointers.
  One way to do this would be to count the number of self-links and create an array with this length instead.
  */

  //Allocate row_ptr and col_idx.
  *row_ptr = (int*)calloc(*N+1, sizeof(int*));
  *col_idx = (int*)calloc(*N_links, sizeof(int*));
  int x = 0;
  for (int i = 0; i < *N; i++){
    //printf("Sorting for row %d of %d\n", i, *N-1);
    for (int j = 0; j < *N_links; j++){
      if (tmp_row[j] == i){
        (*col_idx)[x] = tmp_col[j];
        x++;
      }
    }
    (*row_ptr)[i+1] = x;
  }

  //The temporary arrays for the row and column elements have served their purpose.
  free(tmp_row);
  free(tmp_col);



}
