# Compilation

## Serial code
To compile, link and execute the serial part of the test program, run the following in a Linux terminal:

```terminal
make serial
```

This will test all functions and produce output that should look something like this:

```terminal
-------------------------------------------------------------------------
Testing read_graph_from_file1:
-------------------------------------------------------------------------
Nodes = 50000
Edges = 146823
Timeused by read_graph_from_file1 = 0.185676 seconds
-------------------------------------------------------------------------
Testing count_mutual_links1:
-------------------------------------------------------------------------
Total mutual web linkages = 13165067
Timeused by count_mutual_links1 = 1.772794 seconds
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
Timeused by top_n_webpages = 0.002313 seconds
-------------------------------------------------------------------------
-------------------------------------------------------------------------
Testing read_graph_from_file2:
-------------------------------------------------------------------------
Nodes = 325729
Edges = 1497134
Timeused by read_graph_from_file2 = 0.352823 seconds
-------------------------------------------------------------------------
Testing count_mutual_links2:
-------------------------------------------------------------------------
Total mutual web linkages = 250329403
Timeused by count_mutual_links2 = 0.002085 seconds
-------------------------------------------------------------------------
Testing top_n_webpages:
-------------------------------------------------------------------------
Ranking                Involvements             Web page number
-------------------------------------------------------------------------
1                            56653                         7138
2                            42023                         260553
3                            41871                         236096
4                            41868                         260679
5                            41868                         260678
6                            41868                         260683
7                            41868                         260680
8                            41868                         260685
9                            41868                         260682
10                            41868                         260687
-------------------------------------------------------------------------
Timeused by top_n_webpages = 0.019786 seconds

```

## Parallel code
To compile, link and execute the parallel part of the test program, run the following in a Linux terminal:

```terminal
make parallel
```

This should produce similar output to that of the serial codes, however it fill do this for several number of threads
and thus will print the same tables several times so one can check for consistency of output as well as the
corresponding execution time.
