### Serial code

To execute the serial code, type the following into a linux terminal:

```terminal
make serial
```
This will compile and execute the serial programs with a test case. This gives the ouput:

```terminal
gcc -Ofast -o serial_main.exe serial_main.c count_friends_of_ten.c
./serial_main.exe
Creating matrix...
Entering function...
num_triple_friends = 1706523
Time used = 0.018021

```

### MPI code
To run the MPI code, type the following into a linux terminal:

```terminal
make parallel
```
This will compile and execute the MPI codes with a test case. This gives the output

```terminal
mpicc -Ofast -o mpi_main.exe mpi_count_friends_of_ten.c mpi_main.c
mpirun -n 4 ./mpi_main.exe
Creating matrix...
Entering function...
Time of computation = 0.013436
Time used measure by rank 0 = 0.006455
num_triple_friends = 1706523
Time used = 0.016775
```

You might have to change the number of processes to run the executable with in the makefile depending on your computer.
