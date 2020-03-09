test: test_prog
	./test_prog.exe web-NotreDame.txt

test_prog: test_prog.c
	gcc -fopenmp 	-otest_prog.exe test_prog.c read_graph_from_file1.c read_graph_from_file2.c count_mutual_links1.c count_mutual_links2.c

serial: test_serial
	./test_serial.exe 8-webpages.txt web-NotreDame.txt

parallel: test_parallel
	./test_parallel.exe 8-webpages.txt web-NotreDame.txt

test_serial: test_prog.c
	gcc -otest_serial.exe test_prog.c read_graph_from_file1.c read_graph_from_file2.c count_mutual_links1.c count_mutual_links2.c top_n_webpages.c

test_parallel: test_prog.c
	gcc -fopenmp -otest_parallel.exe test_prog.c read_graph_from_file1.c read_graph_from_file2.c count_mutual_links1.c count_mutual_links2.c top_n_webpages.c

cleanup:
	mv serial_times.txt count_mutual_links1_parallel_results.txt count_mutual_links2_parallel_results.txt results/
