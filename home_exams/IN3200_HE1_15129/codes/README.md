# Compilation

To make the README.md into a README.pdf, just run the following in a Linux terminal.

```terminal
make README
```
A .pdf version of the README is created for easier readability.
Make sure Pandoc and Tex is installed before you do this.

## Serial code

#### Compilation and execution
To compile, link and execute the serial part of the test program, run the following in a Linux terminal:

```terminal
make serial
```

#### Output
The prescription above will test all functions and produce output that should look something like this:

```terminal
-------------------------------------------------------------------------
Testing read_graph_from_file1:
-------------------------------------------------------------------------
Nodes = 50000
Edges = 146823
Timeused by read_graph_from_file1 = 0.174965 seconds
-------------------------------------------------------------------------
Testing count_mutual_links1:
-------------------------------------------------------------------------
Total mutual web linkages = 13165067
Timeused by count_mutual_links1 = 1.747335 seconds
-------------------------------------------------------------------------
Testing top_n_webpages:
-------------------------------------------------------------------------
Ranking                Involvements             Web page number
-------------------------------------------------------------------------
1                            26262                         7138
2                            9674                         246
3                            7892                         7687
4                            7856                         1660
5                            7820                         7604
6                            7820                         7605
7                            7820                         7607
8                            7773                         7606
9                            7045                         18266
10                            6821                         11
-------------------------------------------------------------------------
Timeused by top_n_webpages = 0.002166 seconds
-------------------------------------------------------------------------
-------------------------------------------------------------------------
Testing read_graph_from_file2:
-------------------------------------------------------------------------
Nodes = 50000
Edges = 146823
Timeused by read_graph_from_file2 = 0.030421 seconds
-------------------------------------------------------------------------
Testing count_mutual_links2:
-------------------------------------------------------------------------
Total mutual web linkages = 13165067
Timeused by count_mutual_links2 = 0.000296 seconds
-------------------------------------------------------------------------
Testing top_n_webpages:
-------------------------------------------------------------------------
Ranking                Involvements             Web page number
-------------------------------------------------------------------------
1                            26262                         7138
2                            9674                         246
3                            7892                         7687
4                            7856                         1660
5                            7820                         7604
6                            7820                         7605
7                            7820                         7607
8                            7773                         7606
9                            7045                         18266
10                            6821                         11
-------------------------------------------------------------------------
Timeused by top_n_webpages = 0.002233 seconds
```

## Parallel code

#### Important note!
The parallelized version of the codes use a feature from OpenMP 4.5 or later (array reduction, to be specific), so it's necessary to have a gcc compiler which is compatible with this.


#### Compilation and execution
To compile, link and execute the parallel part of the test program, run the following in a Linux terminal:

```terminal
make parallel
```

This should produce similar output to that of the serial codes, however it will do this for several number of threads
and thus will print the same tables several times so one can check for consistency of output as well as the
corresponding execution time. More detailed analysis of the time measurements and speedup is found in the report.
