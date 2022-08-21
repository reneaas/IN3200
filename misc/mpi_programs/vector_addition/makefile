all: compile execute

compile:
	mpicc -Wall -o vector_addition.exe vector_addition.c

execute:
	mpiexec -n 8 ./vector_addition.exe
