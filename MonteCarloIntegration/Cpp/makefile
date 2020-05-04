parallel: compile_parallel execute_parallel

compile_parallel:
	g++ -O3 -fopenmp -o main.exe main.cpp

execute_parallel:
	./main.exe

serial: compile execute

compile:
	g++ -O3 -fopenmp -o main.exe main.cpp

execute:
	./main.exe
