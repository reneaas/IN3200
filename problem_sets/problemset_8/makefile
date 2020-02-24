all: parallel execute
parallel: exercise3.c
	gcc -fopenmp -oexercise3_parallel.exe exercise3.c

execute:
	./exercise3_parallel.exe 100000
