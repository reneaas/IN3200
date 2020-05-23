mpi: compile_mpi execute_mpi

compile_mpi:
	mpicc -O3 -o mpi_main.exe mpi_main.c functions.c -lm

execute_mpi:
	mpirun -n 4 ./mpi_main.exe

omp: compile_omp execute_omp

compile_omp:
	gcc -O3 -o omp_main.exe omp_main.c -lm -fopenmp

execute_omp:
	./omp_main.exe
