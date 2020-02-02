import os

os.system("gcc -Wall -c copy.c")
os.system("gcc -o copy.exe copy.o")

os.system("./copy.exe")
