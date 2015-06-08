#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

// Tests the steward card in dominion.c
int main (int argc, char** argv) {
    printf("TESTING steward card\n");

    srand(time(NULL));

    int numplayers = 2;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, steward, mine, cutpurse, sea_hag, tribute, smithy};

    printf("RANDOM TESTS\n");

    int numtests = 100;
    for(int i = 0; i < numtests; i++){
        initializeGame(numplayers, k, rand(), &G);
          int money = 0;
          int stewardPos = -1;
          int adventurerPos = -1;
          int i=0;

          int numStewards = 0;
          int numAdventurers = 0;

          while (!isGameOver(&G)) {
            money = 0;
            stewardPos = -1;
            adventurerPos = -1;
            for (i = 0; i < numHandCards(&G); i++) {
              if (handCard(i, &G) == copper)
            money++;
              else if (handCard(i, &G) == silver)
            money += 2;
              else if (handCard(i, &G) == gold)
            money += 3;
              else if (handCard(i, &G) == steward)
            stewardPos = i;
              else if (handCard(i, &G) == adventurer)
            adventurerPos = i;
            }

            if (whoseTurn(&G) == 0) {
              if (stewardPos != -1) {
                struct gameState orig;
                memcpy(&orig, &G, sizeof(struct gameState));

                int choice1 = -1;
                switch(rand() % 3){
                    case 1:
                        choice1 = 1; break;
                    case 2:
                        choice1 = 2; break;
                }

                playCard(stewardPos, choice1, -1, -1, &G); 
                
                int player = whoseTurn(&G);

                if(choice1 == 1){
                    assert(G.handCount[player] == orig.handCount[player] + 1);
                }else if(choice1 == 2){
                    assert(G.coins == orig.coins + 2);
                    assert(G.handCount[player] == orig.handCount[player] - 1);
                }else{
                    assert(G.handCount[player] == orig.handCount[player] - 3);
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
              else if ((money >= 4) && (numStewards < 2)) {
                buyCard(steward, &G);
                numStewards++;
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
