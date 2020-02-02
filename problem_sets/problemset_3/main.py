import os


os.system("gcc -O0 -c main.c")
os.system("gcc -O0 -o main.exe main.o -lm")
os.system("./main.exe")
