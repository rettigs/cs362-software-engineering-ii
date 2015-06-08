#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

// Tests the adventurer card in dominion.c
int main (int argc, char** argv) {
    printf("TESTING adventurer card\n");

    srand(time(NULL));

    printf("RANDOM TESTS\n");

    int numtests = 1000;
    int NUMQUESTIONS = 3;
    int bad = 0;
    for(int i = 0; i < numtests; i++){
        int numplayers = rand() % (MAX_PLAYERS - 1) + 2; // Value between 2 and 4.
        struct gameState G;
        int k[10] = {adventurer, gardens, embargo, village, steward, mine, cutpurse, sea_hag, tribute, smithy};

        initializeGame(numplayers, k, rand(), &G);

        int player = rand() % numplayers;
        G.whoseTurn = player;
        
        int bonus = rand() % 50;
        int choice1 = rand() % 50;
        int choice2 = rand() % 50;
        int choice3 = rand() % 50;
        int handPos = rand() % MAX_HAND;

        struct gameState orig;
        memcpy(&orig, &G, sizeof(struct gameState));

        cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);

        if(G.handCount[player] != orig.handCount[player] + 2){
            printf("TEST FAILED: Player %d didn't draw 2 cards.\n", player);
            bad++;
        }

        int cardDrawn1 = G.hand[player][G.handCount[player] - 1];
        if(cardDrawn1 != copper && cardDrawn1 != silver && cardDrawn1 != gold){
            printf("TEST FAILED: Player %d's newest card isn't money.\n", player);
            bad++;
        }

        int cardDrawn2 = G.hand[player][G.handCount[player] - 2];
        if(cardDrawn2 != copper && cardDrawn2 != silver && cardDrawn2 != gold){
            printf("TEST FAILED: Player %d's second newest card isn't money.\n", player);
            bad++;
        }
    }

    printf("%d of %d TESTS PASSED\n", numtests * NUMQUESTIONS - bad, numtests * NUMQUESTIONS);
}
