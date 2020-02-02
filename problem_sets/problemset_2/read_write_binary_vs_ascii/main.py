import os

os.system("gcc -O3 -c read.c")
os.system("gcc -O3 -o read.exe read.o")

os.system("./read.exe")
