serial: serial_main execute_serial

parallel: parallel_main parallel_execute

serial_main:
	gcc -Ofast -o serial_main.exe serial_main.c count_friends_of_ten.c

execute_serial:
	./serial_main.exe

parallel_main:
	mpicc -03 -o mpi_main.exe $(wildcard mpi*.c) -mtune=native -march=native

parallel_execute:
	mpirun -n 4 ./mpi_main.exe
