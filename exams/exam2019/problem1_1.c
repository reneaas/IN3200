#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int main()
{
	int N = 25000;
	srand(1);
	int **a = (int**)malloc(N*sizeof(int*));
	int **a_new = malloc(N*sizeof *a);
	int **b = malloc(N*sizeof *b);
	for (int i = 0; i < N; i++){
		a[i] = (int*)malloc(N*sizeof(int));
		a_new[i] = malloc(N*sizeof *a_new[i]);
		b[i] = malloc(N*sizeof *b[i]);
	}

	double *c = malloc(N*sizeof *c);
	double *c_new = malloc(N*sizeof *c_new);
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
	double pi_div_n = 3.1415926/N;
	double n_div = 1/N;
	double tmp = 1, exponential = exp(n_div);
	int tmp2;


	start = clock();
	for (int i = 0; i < N; i++){
	//	c[i] = exp(i*n_div) + sin(i*pi_div_n);
		c[i] = exp(i/N) + sin(3.1415926*i/N);
		//tmp *= exponential;
		tmp2 = d[i];
		for (int j = 0; j < N; j++){
			a[i][j] = b[i][j] + tmp2*e[j];
		}
	}
	end = clock();
	timeused = (double) (end-start)/CLOCKS_PER_SEC;
	printf("timeused before = %lf\n", timeused);

	for (int i = 0; i < N; i++){
		c[i] = 0.;
		for (int j = 0; j < N; j++){
			a[i][j] = 0;
		}
	}

	start = clock();
	for (int i = 0; i < N; i++){
		c_new[i] = exp(i/N) + sin(3.1415926*i/N);
		for (int j = 0; j < N; j++){
			a_new[i][j] = b[i][j] + d[i]*e[j];
		}
	}
	end = clock();
	timeused = (double) (end-start)/CLOCKS_PER_SEC;
	printf("timeused = %lf\n", timeused);


}
