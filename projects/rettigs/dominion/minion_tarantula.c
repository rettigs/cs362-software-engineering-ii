#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

int debug = 0;

void fail(){
    printf("1\n");
    exit(EXIT_SUCCESS);
}

// Tests the minion card in dominion.c
int main (int argc, char** argv) {
    if(argc > 2) debug = 1;

    srand(atoi(argv[1]));

    int numplayers = rand() % (MAX_PLAYERS - 1) + 2; // Value between 2 and 4.
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, steward, mine, cutpurse, sea_hag, tribute, smithy};

    initializeGame(numplayers, k, rand(), &G);

    int player = rand() % numplayers;
    G.whoseTurn = player;

    for(int i = 0; i < numplayers; i++){
        G.handCount[i] = rand() % 10 + 1; // Random number of cards from 1-10
        for(int j = 0; j < G.handCount[i]; j++){
            G.hand[i][j] = rand() % 27; // Random card from 0-26
        }
    }
    
    int bonus = rand() % 50;
    int choice1 = rand() % 2;
    int choice2 = (choice1 + 1) % 2; // Choose either choice1 or choice2, 50/50 chance
    int choice3 = 0;
    int handPos = rand() % MAX_HAND;

    struct gameState orig;
    memcpy(&orig, &G, sizeof(struct gameState));

    if(debug) printf("Player %d's turn\n", player);
    if(debug) printf("Choice1: %d\n", choice1);
    if(debug) printf("Choice2: %d\n", choice2);
    
    for(int i = 0; i < numplayers; i++){
        if(debug) printf("Player %d old handCount: %d\n", i, G.handCount[i]);
    }

    for(int i = 0; i < numplayers; i++){
        for(int j = 0; j < G.handCount[i]; j++){
            if(debug) printf("Player %d old card at pos %d: %d\n", i, j, G.hand[i][j]);
        }
    }

    cardEffect(minion, choice1, choice2, choice3, &G, handPos, &bonus);
    
    for(int i = 0; i < numplayers; i++){
        if(debug) printf("Player %d new handCount: %d\n", i, G.handCount[i]);
    }

    for(int i = 0; i < numplayers; i++){
        for(int j = 0; j < G.handCount[i]; j++){
            if(debug) printf("Player %d new card at pos %d: %d\n", i, j, G.hand[i][j]);
        }
    }

    if(G.numActions != orig.numActions + 1){
        if(debug) printf("numActions not incremented by 1; went from %d to %d\n", orig.numActions, G.numActions);
        fail();
    }

    if(choice1 && G.coins != orig.coins + 2){
        if(debug) printf("coins not incremented by 2; went from %d to %d\n", orig.coins, G.coins);
        fail();
    }

    if(choice2 && G.handCount[player] != 4){
        if(debug) printf("original player %d's handcount isn't 4; went from %d to %d\n", player, orig.handCount[player], G.handCount[player]);
        fail();
    }

    if(choice2){
        for(int i = 0; i < numplayers; i++){
            if(i != player){
                if(orig.handCount[i] > 4){
                    if(G.handCount[i] != 4){
                        if(debug) printf("player %d handcount isn't 4\n", player);
                        fail();
                    }
                }else{
                    if(G.handCount[i] > 4){
                        if(debug) printf("player %d handcount is greater than 4\n", player);
                        fail();
                    }
                }
            }
        }
    }

    printf("0\n");
    exit(EXIT_SUCCESS);
}
