#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
{
  int max_line_length = 128;
  char *line_buffer = (char*)malloc(max_line_length*sizeof(char));
  FILE *fp = fopen(filename, "r");

  //Read the first 2 lines of the file. We want the third one to extract the desired parameters.
  fgets(line_buffer, max_line_length, fp);
  fgets(line_buffer, max_line_length, fp);


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
  int *row_count = (int*)calloc(*N, sizeof(int));

  int FromNodeId, ToNodeId, self_link_counter;
  self_link_counter = 0;
  int l = 0;
  for (int k = 0; k < *N_links; k++){
    fscanf(fp, "%d %d", &FromNodeId, &ToNodeId);
    if (FromNodeId != ToNodeId){
      tmp_col[l] = FromNodeId;
      tmp_row[l] = ToNodeId;
      row_count[ToNodeId] += 1;
      l++;
    }
    else{
      self_link_counter++;
    }
  }
  fclose(fp);

  //Create the row_ptr array using the row_count array.
  *row_ptr = (int*)calloc(*N+1, sizeof(int*));
  int count = 0;
  for (int i = 0; i < *N; i++){
    count += row_count[i];
    (*row_ptr)[i+1] = count;
  }
  free(row_count);        //Free up memory, it has served its purpose at this point.


  *N_links -= self_link_counter;        //Update number of links by removing number of self-links.


  //We copy FromNodeIds and ToNodeIds into arrays of the correct size to simplify sorting later:
  *col_idx = (int*)calloc(*N_links, sizeof(int*));
  int *row_elems = (int*)calloc(*N_links, sizeof(int));
  for (int i = 0; i < *N_links; i++){
    (*col_idx)[i] = tmp_col[i];
    row_elems[i] = tmp_row[i];
  }
  //Now the values of interest are copied into arrays of the correct length, so we free up memory.
  free(tmp_col);
  free(tmp_row);

  //Now we sort the row_elems and *col_idx arrays using shell sort:
  int tmp1, tmp2, i, j, gap;
  for (gap = *N_links/2; gap > 0; gap /= 2){
    for (i = gap; i < *N_links; i++){
      tmp1 = row_elems[i];
      tmp2 = (*col_idx)[i];
      for (j = i; j >= gap && row_elems[j-gap] > tmp1; j -= gap){
        row_elems[j] = row_elems[j-gap];
        (*col_idx)[j] = (*col_idx)[j-gap];
      }
      row_elems[j] = tmp1;
      (*col_idx)[j] = tmp2;
    }
  }

  free(row_elems);        //Free up memory, we no longer need row_elems.
}
