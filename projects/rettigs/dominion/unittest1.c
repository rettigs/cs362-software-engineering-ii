#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

// Tests compare() in dominion.c
int main(int argc, char **argv)
{
    printf("TESTING compare\n");
    printf("RANDOM TESTS\n");

    srand(time(NULL));
    int numtests = 1000;
    for(int i = 0; i < numtests; i++){
        int a = rand(); // a is a positive integer
        int b = a - 1 - rand() % 1000000; // By definition, a > b

        switch(rand() % 3){
            case 0:
                assert(compare(&a, &b) == 1); break;
            case 1:
                assert(compare(&b, &a) == -1); break;
            case 2:
                assert(compare(&a, &a) == 0); break;
        }
    }

    printf("ALL TESTS OK\n");
}
