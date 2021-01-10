all: compile execute

compile:
	mpicc -g -Wall -o trapezoidal.exe trapezoidal.c

execute:
	mpiexec -n 4 ./trapezoidal.exe
