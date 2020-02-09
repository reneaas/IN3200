from os import system

system("gcc -c main.c")
system("gcc -o main.exe main.o -lm")

system("./main.exe")
