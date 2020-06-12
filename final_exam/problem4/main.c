#include <stdlib.h>
#include <stdio.h>
#include <random.h>

int main(int argc, char const *argv[]) {
    return 0;
}


void advance_one_day(int *row_ptr, int *col_idx, int *state_old, int *state_new, double f, int N)
{
    int person1, person2, person1_state, person2_state;
    double u;
    int i,j;
    int max_int = 1000000;
    double max_inv = 1./max_int;
    //Iterate over every person i in the population
    for (i = 0; i < N; i++){
        person1 = i; //Extract ID of person 1
        person1_state = state_old[person1]; //Extract state of person 1

        //Only check the interactions if the person is not immune which is denoted with state = 2.
        if (person1_state != 2){
            //The matrix is symmetric, so we only want to check interactions below the diagonal which corresponds to col_idx[j] < i.
            for (j = row_ptr[i]; j < row_ptr[i+1] && col_idx[j] < i; j++){
                person2 = col_idx[j]; //Extract id of person 2
                person2_state = state_old[person2]; //Extract state of person 2

                //If person 1 is sick, check if person 2 gets infected.
                if (person1_state == 1 && person2_state == 0){
                    u = (double) (rand() % max_int)*max_inv;
                    if (u < f){
                        state_new[person2] = 1; //Person 2 gets infected.
                    }
                }
                //If person 2 is sick, check if person 1 gets infected.
                if (person1_state == 0 && person2_state == 1){
                    u = (double) (rand() % max_int)*max_inv;
                    if (u < f){
                        state_new[person1] = 1; //Person 1 gets infected.
                    }
                }
            }
        }
    }
    //Copy all the values from states_new to states_old.
    for (i = 0; i < N; i++) state_old[i] = state_new[i];
}
