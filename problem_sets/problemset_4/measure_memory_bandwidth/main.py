from os import system

system("gcc -Ofast -c main.c")
system("gcc -Ofast -o main.exe main.o")

system("./main.exe")
