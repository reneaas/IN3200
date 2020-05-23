#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include <random>

using namespace std;

void Gaussian_Elimination(double *A, double *b, double *y, int n);

int main()
{
    int n = 5000;
    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution<double> RandomNumberGenerator(0,1);

    double *A = new double[n*n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            A[i*n+j] = RandomNumberGenerator(gen);
        }
    }


    double *b = new double[n];
    double *y = new double[n];

    for (int i = 0; i < n; i++){
        b[i] = RandomNumberGenerator(gen);
        y[i] = RandomNumberGenerator(gen);
    }

    #ifdef _OPENMP
    {
        double start, end, timeused;
        start = omp_get_wtime();
        Gaussian_Elimination(A, b, y, n);
        end = omp_get_wtime();
        timeused = end-start;
        printf("Timeused = %lf\n", timeused);
    }
    #else
    {
        clock_t start, end;
        double timeused;
        start = clock();
        Gaussian_Elimination(A, b, y, n);
        end = clock();
        timeused = (double) (end-start)/CLOCKS_PER_SEC;
        printf("Timeused = %lf\n", timeused);
    }
    #endif

    delete[] A;
    delete[] y;
    delete[] b;
}

void Gaussian_Elimination(double *A, double *b, double *y, int n)
{
    int i, j, k;
    double tmp;
    #ifdef _OPENMP
    {
        for (k = 0; k < n; k++){
            //tmp = A[k*n+k];
            #pragma omp parallel for private(j)
            for (j = k+1; j < n; j++){
                A[k*n + j] = A[k*n + j]/A[k*n + k];
            }
            y[k] = b[k]/A[k*n+k];
            A[k*n + k] = 1.;
            #pragma omp parallel for private(i, j)
            for (i = k+1; i < n; i++){
                for (j = k+1; j < n; j++){
                    A[i*n+j] = A[i*n+j] - A[i*n+k]*A[k*n+j];
                }
                b[i] = b[i] - A[i*n+k]*y[k];
                A[i*n+k] = 0.;
            }
        }
    }
    #else
    {
        for (k = 0; k < n; k++){
            //tmp = A[k*n+k];
            for (j = k+1; j < n; j++){
                A[k*n + j] = A[k*n + j]/A[k*n + k];
            }
            y[k] = b[k]/A[k*n+k];
            A[k*n + k] = 1.;

            for (i = k+1; i < n; i++){
                for (j = k+1; j < n; j++){
                    A[i*n+j] = A[i*n+j] - A[i*n+k]*A[k*n+j];
                }
                b[i] = b[i] - A[i*n+k]*y[k];
                A[i*n+k] = 0.;
            }
        }
    }
    #endif
}
