#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

// Tests the minion card in dominion.c
int main (int argc, char** argv) {
    printf("TESTING minion card\n");

    srand(time(NULL));

    int numplayers = 2;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    printf("RANDOM TESTS\n");

    int numtests = 100;
    for(int i = 0; i < numtests; i++){
        initializeGame(numplayers, k, rand(), &G);
          int money = 0;
          int minionPos = -1;
          int adventurerPos = -1;
          int i=0;

          int numMinions = 0;
          int numAdventurers = 0;

          while (!isGameOver(&G)) {
            money = 0;
            minionPos = -1;
            adventurerPos = -1;
            for (i = 0; i < numHandCards(&G); i++) {
              if (handCard(i, &G) == copper)
            money++;
              else if (handCard(i, &G) == silver)
            money += 2;
              else if (handCard(i, &G) == gold)
            money += 3;
              else if (handCard(i, &G) == minion)
            minionPos = i;
              else if (handCard(i, &G) == adventurer)
            adventurerPos = i;
            }

            if (whoseTurn(&G) == 0) {
              if (minionPos != -1) {
                struct gameState orig;
                memcpy(&orig, &G, sizeof(struct gameState));

                int choice1 = -1;
                int choice2 = -1;
                switch(rand() % 3){
                    case 1:
                        choice1 = 1; break;
                    case 2:
                        choice2 = 1; break;
                }

                playCard(minionPos, choice1, choice2, -1, &G); 
                
                int player = whoseTurn(&G);

                assert(G.numActions == orig.numActions + 1);
                if(choice1 == 1){
                    assert(G.coins == orig.coins + 2);
                }else if(choice2 == 1){
                    for(int eachPlayer = 0; eachPlayer < numplayers; eachPlayer++){
                        assert(G.handCount[eachPlayer] <= 4);
                    }
                }
                money = 0;
                i=0;
            while(i<numHandCards(&G)){
              if (handCard(i, &G) == copper){
                playCard(i, -1, -1, -1, &G);
                money++;
              }
              else if (handCard(i, &G) == silver){
                playCard(i, -1, -1, -1, &G);
                money += 2;
              }
              else if (handCard(i, &G) == gold){
                playCard(i, -1, -1, -1, &G);
                money += 3;
              }
              i++;
            }
              }

              if (money >= 8) {
                buyCard(province, &G);
              }
              else if (money >= 6) {
                buyCard(gold, &G);
              }
              else if ((money >= 4) && (numMinions < 2)) {
                buyCard(minion, &G);
                numMinions++;
              }
              else if (money >= 3) {
                buyCard(silver, &G);
              }

              endTurn(&G);
            }
            else {
              if (adventurerPos != -1) {
            playCard(adventurerPos, -1, -1, -1, &G); 
            money = 0;
            i=0;
            while(i<numHandCards(&G)){
              if (handCard(i, &G) == copper){
                playCard(i, -1, -1, -1, &G);
                money++;         
              }
              else if (handCard(i, &G) == silver){
                playCard(i, -1, -1, -1, &G);
                money += 2;
              }
              else if (handCard(i, &G) == gold){
                playCard(i, -1, -1, -1, &G);
                money += 3;
              }
              i++;
            }
              }

              if (money >= 8) {
                buyCard(province, &G);
              }
              else if ((money >= 6) && (numAdventurers < 2)) {
            buyCard(adventurer, &G);
            numAdventurers++;
              }else if (money >= 6){
                buyCard(gold, &G);
                }
              else if (money >= 3){
                buyCard(silver, &G);
              }
              
              endTurn(&G);      
            }
          } // end of While
    }

    printf("ALL TESTS OK\n");
}
