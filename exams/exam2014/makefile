serial: compile_serial execute_serial

compile_serial:
	g++ -O3 -o serial_main.exe main.cpp -march=native

execute_serial:
	./serial_main.exe

parallel: compile_omp execute_omp

compile_omp:
	g++ -O3 -o parallel_main.exe main.cpp -fopenmp -march=native

execute_omp:
	./parallel_main.exe
