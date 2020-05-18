serial: test_serial.exe
	./test_serial.exe test_webpages.txt test_webpages.txt

parallel: test_parallel.exe
	./test_parallel.exe test_webpages.txt web-NotreDame.txt

test_serial.exe:
	gcc -O3 -o $@ $(wildcard *.c) -fopt-info -march=native

test_parallel.exe:
	gcc -O3 -fopenmp -o $@ $(wildcard *.c) -march=native

clean:
	rm test_serial.exe test_parallel.exe

README:
	pandoc README.md -o README.pdf
