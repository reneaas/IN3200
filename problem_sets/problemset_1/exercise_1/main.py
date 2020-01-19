import os

os.system("gcc -Wall -c main.c -lm")
os.system("gcc -Wall -o main.exe main.o -lm")
os.system("./main.exe")
