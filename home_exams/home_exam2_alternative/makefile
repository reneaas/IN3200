parallel: parallel_main parallel_execute

parallel_main:
	mpicc -Ofast -o mpi_main.exe $(wildcard mpi*.c)

parallel_execute:
	mpirun -n 4 ./mpi_main.exe
