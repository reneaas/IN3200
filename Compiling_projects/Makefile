
PROGRAMS = main.exe

.PHONY : clean

main.exe : main.o helper.o helper.h
	gcc main.o helper.o -o main.exe

helper.o : helper.c
	gcc -c helper.c

main.o : main.c helper.h
	gcc -c main.c


tar : compiling_projects.pdf
	tar cvzf compiling_projects.tar.gz Makefile compiling_projects.md \
	compiling_projects.pdf helper.h helper.c main.c

compiling_projects.pdf : compiling_projects.md
	pandoc compiling_projects.md -o compiling_projects.pdf

clean :
	rm -f *.o $(PROGRAMS)
