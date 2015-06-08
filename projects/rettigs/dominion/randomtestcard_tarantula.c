#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

// Tests the council room card in dominion.c
int main (int argc, char** argv) {
    srand(atoi(argv[0]));

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

    cardEffect(council_room, choice1, choice2, choice3, &G, handPos, &bonus);

    int failure = 0;
    for(int i = 0; i < numplayers; i++){
        if(i == player){
            if(G.handCount[i] != orig.handCount[i] + 3){
                failure = 1;
                break;
            }
        }else{
            if(G.handCount[i] != orig.handCount[i] + 1){
                failure = 1;
                break;
            }
        }
    }

    printf("%d\n", failure);
}
