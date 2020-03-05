all: main1 main2 execute_main1 execute_main2 

main1: main1.c
	gcc -omain1.exe main1.c read_graph_from_file1.c count_mutual_links1.c top_n_webpages.c

main2: main2.c
	gcc -omain2.exe main2.c read_graph_from_file2.c count_mutual_links2.c top_n_webpages.c

execute_main1:
	./main1.exe 8-webpages.txt

execute_main2:
	./main2.exe web-NotreDame.txt
