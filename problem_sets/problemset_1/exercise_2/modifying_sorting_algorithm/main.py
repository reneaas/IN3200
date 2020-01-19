import os

os.system("gcc -c main.c -lm")
os.system("gcc -o main.exe main.o -lm")

os.system("./main.exe")
