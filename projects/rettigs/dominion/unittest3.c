#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

// Tests shuffle() in dominion.c
int main(int argc, char **argv)
{
    printf("TESTING kingdomCards\n");

    srand(time(NULL));

    int numplayers = rand() % (MAX_PLAYERS - 1) + 1;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(numplayers, k, rand(), &G);

    printf("RANDOM TESTS\n");

    int numtests = 1000;
    int times_unshuffled = 0;
    for(int i = 0; i < numtests; i++){
        // Copy original gamestate for later comparison
        struct gameState orig;
        memcpy(&orig, &G, sizeof(struct gameState));

        int player = rand() % numplayers;
        shuffle(player, &G);
        if(memcmp(&orig.deck[player], &G.deck[player], sizeof(int)*MAX_DECK) != 0) times_unshuffled++;
    }

    printf("DECK PROPERLY SHUFFLED %d/%d TIMES\n", numtests - times_unshuffled, numtests);

    assert(times_unshuffled < numtests / 2); //Assert that shuffle() changed the card order at least half of the time.

    printf("ALL TESTS OK\n");
}
