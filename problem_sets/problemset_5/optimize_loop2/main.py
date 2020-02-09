from os import system

system("gcc -O3 -c main.c")
system("gcc -O3 -o main.exe main.o -lm")
system("./main.exe")
