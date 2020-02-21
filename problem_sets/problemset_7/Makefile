all: exercise1 exercise2 exercise3 test execute

exercise1: exercise1.c
	gcc -fopenmp -oexercise1.exe exercise1.c -lm

exercise2: exercise2.c
	gcc -fopenmp -oexercise2.exe exercise2.c

exercise3: exercise3.c
	gcc -fopenmp -oexercise3.exe exercise3.c

test: test.c
	gcc -O3 -otext.exe test.c

execute: exercise3.exe
	./exercise3.exe 400 400
