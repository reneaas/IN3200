# MPI Guidance

## Setting up MPI Universe:

```c
MPI_Init(&argc, &argv[]); //Create Universe
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //How many processes there is (comm_sz)
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Assigns ranks to the processes
```

## Inputs
Only process 0 can take input from terminal, so you can use

```c
if (my_rank == 0){
  printf("Input values ...\n");
  scanf("%d ....", &some_int ,...);
}
```

## Distribute (broadcast) information with MPI_Bcast to all processes
To distribute information among the processes, one can use the following function

```c
MPI_Bcast{
          void *buffer,
          int count,
          MPI_DOUBLE_Datatype datatype,
          int root,
          MPI_Comm comm
          }

```
