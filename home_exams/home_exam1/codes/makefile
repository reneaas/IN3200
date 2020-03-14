serial: test_serial.exe
	./test_serial.exe test_webpages.txt web-NotreDame.txt

parallel: test_parallel.exe
	./test_parallel.exe test_webpages.txt web-NotreDame.txt && python3 plot.py

test: test_cml
	./test_cml.exe test_webpages.txt

test_serial.exe:
	gcc -O3 -otest_serial.exe $(wildcard *.c)

test_parallel.exe:
	gcc -O3 -fopenmp -otest_parallel.exe $(wildcard *.c)

clean:
	rm test_serial.exe test_parallel.exe
