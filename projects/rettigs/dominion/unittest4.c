#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

// Tests discardCard() in dominion.c
int main(int argc, char **argv)
{
    printf("TESTING discardCard\n");

    srand(time(NULL));

    int numplayers = rand() % (MAX_PLAYERS - 1) + 1;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(numplayers, k, rand(), &G);

    printf("RANDOM TESTS\n");

    int numtests = 100;
    for(int i = 0; i < numtests; i++){
        // Copy original gamestate for later comparison
        struct gameState orig;
        memcpy(&orig, &G, sizeof(struct gameState));

        int trash = rand() % 2;
        int player = rand() % numplayers;
        if(G.handCount[player] > 0){
            discardCard(G.handCount[player] - 1, player, &G, trash);
            assert(orig.handCount[player] - 1 == G.handCount[player]);
            if(!trash) assert(orig.playedCardCount + 1 == G.playedCardCount);
        }
    }

    printf("ALL TESTS OK\n");
}
