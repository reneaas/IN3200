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

```c++
MPI_Bcast(void* buffer,
          int count,
          MPI_DOUBLE_Datatype datatype,
          int root,
          MPI_Comm comm)
```

## Scatter data evenly among the processes
This function assumes that the data to be distributed among the processes
are divisible with comm_sz.
```c++
MPI_Scatter(const void *sendbuf,
            int sendcount,
            MPI_Datatype sendtype,
            void *recvbuf,
            int recvcount,
            MPI_Datatype recvtype,
            int root,
            MPI_Comm comm)
```
Note that sendcount and recvcount are the same here and they are not the same as the length of the sendbuf.

## Gather data from all processes to process 0
```c++
MPI_Gather(const void *sendbuf,
          int sendcount,
          MPI_Datatype sendtype,
          void *recvbuf,
          int recvcount,
          MPI_Datatype recvtype,
          int root,
          MPI_Comm comm)

```            


## MPI_Allgather

```c++
MPI_Allgather(const void *sendbuf,
              int sendcount,
              MPI_Datatype sendtype,
              void *recvbuf,
              int recvcount,
              MPI_Datatype recvtype,
              MPI_Comm comm)
```
