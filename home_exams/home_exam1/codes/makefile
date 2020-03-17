serial: test_serial.exe
	./test_serial.exe test_webpages.txt web-NotreDame.txt

parallel: test_parallel.exe
	./test_parallel.exe test_webpages.txt web-NotreDame.txt && python3 plot.py

test_serial.exe:
	gcc -O3 -o $@ $(wildcard *.c)

test_parallel.exe:
	gcc -O3 -fopenmp -o $@ $(wildcard *.c)

clean:
	rm test_serial.exe test_parallel.exe
