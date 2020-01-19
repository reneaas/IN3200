import os

os.system("gcc -O3 -c main.c -lm")
os.system("gcc -O3 -o main.exe main.o -lm")

os.system("./main.exe")
