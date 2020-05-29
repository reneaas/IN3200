#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[]) {
    clock_t start, end;
    double timeused;

    int N = 2000;
    double N_div = 1./N;
    int iterations = (int) pow(2,10);
    double s = 0;

    //First with no optimization attempt:
    start = clock();
    for (int i = 0; i < iterations; i++){
        for (int j = 0; j < iterations; j++){
            for (int k = 0; k < iterations; k++){
                s += 1./N;
            }
        }
    }
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused with no optimization = %lf\n", timeused);
    printf("s = %lf\n", s);
    s = 0.;
    //Next we use the n_div optimization
    start = clock();
    for (int i = 0; i < iterations; i++){
        for (int j = 0; j < iterations; j++){
            for (int k = 0; k < iterations; k++){ 
                s += N_div;
            }
        }
    }
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused with N_div optimization = %lf\n", timeused);
    printf("s = %lf\n", s);
    s = 0.;
    //Next we use the explicit (1.0/N) optimization;
    start = clock();
    for (int i = 0; i < iterations; i++){
        for (int j = 0; j < iterations; j++){
            for (int k = 0; k < iterations; k++){
                s += (1./N);
            }
        }
    }
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    printf("Timeused with (1.0/N) optimization = %lf\n", timeused);
    printf("s = %lf\n", s);
    s = 0.;

    return 0;
}
