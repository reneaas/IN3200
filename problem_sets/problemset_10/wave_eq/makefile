compile_parallel:
	mpicc -o main.exe main.c -lm

parallel: compile_parallel
	mpiexec -n 4 ./main.exe && python3 plot.py

compile_serial:
	gcc -o serial.exe serial.c -lm

serial: compile_serial
	./serial.exe
