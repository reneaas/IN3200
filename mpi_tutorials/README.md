# MPI Guidance

## Setting up MPI Universe:

```c
MPI_Init(&argc, &argv[]); //Create Universe
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //How many processes there is (comm_sz)
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Assigns ranks to the processes

/* Do stuff here */

MPI_Finalize();
```
You can pass MPI_Init(NULL, NULL) in most cases.

## Inputs
Only process 0 can take input from terminal, so you can use

```c
if (my_rank == 0){
  printf("Input values ...\n");
  scanf("%d ....", &some_int ,...);
}
```

## Collective communication

### Distribute (broadcast) information with MPI_Bcast to all processes
To distribute information among the processes, one can use the following function

```c++
MPI_Bcast(void* buffer,
          int count,
          MPI_DOUBLE_Datatype datatype,
          int root,
          MPI_Comm comm)
```

### Scatter data evenly among the processes
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

### Scatter arbitrary chunks of data among the processes

```c++
MPI_Scatterv(const void *sendbuf,
              const int *sendcounts,
              const int *displs,
              MPI_Datatype sendtype,
              void *recvbuf,
              int recvcount,
              MPI_Datatype recvtype,
              int root,
              MPI_Comm comm)
```
We must create the send buffer *sendbuf* which stores the actual data we want to distribute. The other new and important objects to understand is:
1. *sendcount* stores how many items each process will receive.
2. *displs* is an cumulative array storing how many items the processes receives.


Generally they can be created in the following way.

```c++
int Local_N = N/comm_sz;
int remainder = N % comm_sz;
displs[0] = 0;
for (int rank = 0; rank < comm_sz-1; rank++){
  sendcounts[rank] = number_of_objects[rank];
  displs[rank+1] = displs[rank] + sendcounts[rank];
}
//Account for remainder
sendcounts[comm_sz-1] = number_of_objects[comm_sz-1] + remainder_objects;
```

Below is an example of its usage. It's used to distribute rows a generic (M x N)-matrix among the processes.

```c++
int rows = N/comm_sz;
int row_remainder = (N % comm_sz);

for (int rank = 0; rank < comm_sz-1; rank++){
  n_rows[rank] = rows;
  sendcounts[rank] = n_rows[rank] * N;
  displs[rank+1] = displs[rank] + sendcounts[rank];
}
n_rows[comm_sz-1] = rows + row_remainder;
sendcounts[comm_sz-1] = n_rows[comm_sz-1] * N;
```


### Gather data from all processes to process 0
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


### MPI_Allgather

```c++
MPI_Allgather(const void *sendbuf,
              int sendcount,
              MPI_Datatype sendtype,
              void *recvbuf,
              int recvcount,
              MPI_Datatype recvtype,
              MPI_Comm comm)
```

## Point-to-point communcation
A MPI_Send call must have a matching MPI_Recv call.

Send a message from process tag to process dest.
```c++
MPI_Send(const void *buf,
        int count,
        MPI_Datatype datatype,
        int dest,
        int tag,
        MPI_Comm comm)
```

Recieve message from process tag at process dest.

```c++
MPI_Recv(void *buf,
            int count,
            MPI_Datatype datatype,
            int source,
            int tag,
            MPI_Comm comm,
            MPI_Status *status)
```
Usually, it's sufficient to pass status = MPI_STATUS_IGNORE in this function.

## Reductions

To perform reductions, we can use MPI_Reduce:
```c++
MPI_Reduce(const void *sendbuf,
          void *recvbuf,
          int count,
          MPI_Datatype datatype,
          MPI_Op op,
          int root,
          MPI_Comm comm)
```

If all processes need the result of the reduction, one can use MPI_Allreduce:

```c++
MPI_Allreduce(const void *sendbuf,
              void *recvbuf,
              int count,
              MPI_Datatype datatype,
              MPI_Op op,
              MPI_Comm comm)
```

Here's a list of some useful MPI_op operations:

| Operation | Meaning     |
| :------------- | :------------- |
| MPI_SUM       | Sum       |
| MPI_PROD       | Product      |
| MPI_MAX       | Max value       |
| MPI_MIN       | Min value       |
