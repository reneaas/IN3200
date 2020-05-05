serial: compile execute

parallel: compile_parallel execute_parallel

compile:
	gcc -O3 -o main.exe main.c -lm -fopt-info

execute:
	./main.exe

compile_parallel:
	gcc -O3 -fopenmp -o parallel_main.exe main.c -lm -fopt-info

execute_parallel:
	./parallel_main.exe
