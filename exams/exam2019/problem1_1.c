#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int main()
{
	int N = 25000;
	srand(1);
	int **a = (int**)malloc(N*sizeof(int*));
	int **b = malloc(N*sizeof *b);
	for (int i = 0; i < N; i++){
		a[i] = (int*)malloc(N*sizeof(int));
		b[i] = malloc(N*sizeof *b[i]);
	}

	double *c = malloc(N*sizeof *c);
	int *d = malloc(N*sizeof *d);
	int *e = malloc(N*sizeof *e);

	for (int i = 0; i < N; i++){
		d[i] = rand() % 10;
		e[i] = rand() % 10;
		for (int j = 0; j < N; j++){
			b[i][j] = rand() % 10;
		}
	}

	clock_t start, end;
	double timeused;
	double exponential = exp(1.0/N);
	double tmp = 1;
	int tmp2;
	double pi_div_n = 3.1415926/N;
	double n_div = 1/N;
	start = clock();
	for (int i = 0; i < N; i++) c[i] = exp(i*n_div) + sin(pi_div_n*i);

	for (int i = 0; i < N; i+=4){
		for (int j = 0; j < N; j++){
			a[i][j] = b[i][j] + d[i]*e[j];
			a[i+1][j] = b[i+1][j] + d[i+1]*e[j];
			a[i+2][j] = b[i+2][j] + d[i+2]*e[j];
			a[i+3][j] = b[i+3][j] + d[i+3]*e[j];
		}
	}
	for (int i = N - N%4; i < N; i++){
		for (int j = 0; j < N; j++){
			a[i][j] = b[i][j] + d[i]*e[j];
		}
	}


	end = clock();
	timeused = (double) (end-start)/CLOCKS_PER_SEC;
	printf("timeused = %lf\n", timeused);

	start = clock();
	for (int i = 0; i < N; i++){
		c[i] = exp(1.0*i/N) + sin(3.1415926*i/N);
		for (int j = 0; j < N; j++){
			a[i][j] = b[i][j] + d[i]*e[j];
		}
	}
	end = clock();
	timeused = (double) (end-start)/CLOCKS_PER_SEC;
	printf("timeused before = %lf\n", timeused);

}


/*
for (int i = 0; i < N; i++){
	c[i] = exp(1.0*i/N) + sin(3.1415926*i/N);
	for (int j = 0; j < N; j++){
		a[j][i] = b[j][i] + d[j]*e[i];
	}
}
*/
