from os import system

system("gcc -O3 -c main.c -fopt-info") #-fopt-info flag gives information about what the optimization the (gcc) compiler performed.

system("gcc -O3 -o main.exe main.o")

system("./main.exe")
