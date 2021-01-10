all: compile execute

compile:
	mpicc -g -o stochastic_matrix.exe stochastic_matrix.c

execute:
	mpiexec -n 2 ./stochastic_matrix.exe
