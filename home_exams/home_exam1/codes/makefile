serial: test_serial.exe
	./test_serial.exe test_webpages.txt test_webpages.txt

parallel: test_parallel.exe
	./test_parallel.exe test_webpages.txt test_webpages.txt

test: test_cml
	./test_cml.exe test_webpages.txt


test_serial.exe:
	gcc -Ofast -otest_serial.exe test_prog.c read_graph_from_file1.c read_graph_from_file2.c count_mutual_links1.c count_mutual_links2.c top_n_webpages.c

test_parallel.exe:
	gcc -Ofast -fopenmp -otest_parallel.exe test_prog.c read_graph_from_file1.c read_graph_from_file2.c count_mutual_links1.c count_mutual_links2.c top_n_webpages.c

cleanup:
	mv serial_times.txt count_mutual_links1_parallel_results.txt count_mutual_links2_parallel_results.txt results/


test_cml:
	gcc -Ofast -otest_cml.exe main.c read_graph_from_file1.c count_mutual_links1.c top_n_webpages.c
