#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

#define V 1 // verbose?

int main (int argc, char** argv) {

    FILE *outs = fopen("gameResults.out", "w");
    if(outs == NULL){
        perror("Could not open write stream for gameResults.out");
        exit(EXIT_FAILURE);
    }

  struct gameState G;
  int k[10];
  selectKingdomCards(atoi(argv[1]), k);

  int players = atoi(argv[1]) % 3 + 2;

  fprintf(outs, "Starting game with %d players\n", players);
  if(V) printf("Starting game with %d players\n", players);
  
  initializeGame(players, k, atoi(argv[1]), &G);
  
  while (!isGameOver(&G)) {
    int curplayer = whoseTurn(&G);

    /* Play action cards */
	for(int i = 0; i < numHandCards(&G) && G.numActions > 0; i++){
        char playcardname[12+1]; // Max length of card name plus null terminator
        cardNumToName(G.hand[curplayer][i], playcardname);
        if(playCard(i, -1, -1, -1, &G) >= 0){
            fprintf(outs, "[Player %d] Played %s\n", curplayer, playcardname);
            if(V) printf("[Player %d] Played %s\n", curplayer, playcardname);
        }else{
            if(V) printf("[Player %d] Couldn't play %s\n", curplayer, playcardname);
        }
    }

    /* Play money cards */
	for(int i = 0; i < numHandCards(&G); i++){
	  if (handCard(i, &G) == copper){
	    playCard(i, -1, -1, -1, &G);
        char playcardname[12+1]; // Max length of card name plus null terminator
        cardNumToName(i, playcardname);
        fprintf(outs, "[Player %d] Played %s\n", curplayer, playcardname);
        if(V) printf("[Player %d] Played %s\n", curplayer, playcardname);
	  }
	  else if (handCard(i, &G) == silver){
	    playCard(i, -1, -1, -1, &G);
        char playcardname[12+1]; // Max length of card name plus null terminator
        cardNumToName(i, playcardname);
        fprintf(outs, "[Player %d] Played %s\n", curplayer, playcardname);
        if(V) printf("[Player %d] Played %s\n", curplayer, playcardname);
	  }
	  else if (handCard(i, &G) == gold){
	    playCard(i, -1, -1, -1, &G);
        char playcardname[12+1]; // Max length of card name plus null terminator
        cardNumToName(i, playcardname);
        fprintf(outs, "[Player %d] Played %s\n", curplayer, playcardname);
        if(V) printf("[Player %d] Played %s\n", curplayer, playcardname);
	  }
	}

    fprintf(outs, "[Player %d] Coins: %d\n", curplayer, G.coins);
    if(V) printf("[Player %d] Coins: %d\n", curplayer, G.coins);

    /* Buy more cards */
    while(G.numBuys > 0 && !isGameOver(&G)){
        int buycard = floor(Random() * 26);
        char buycardname[12+1]; // Max length of card name plus null terminator
        cardNumToName(buycard, buycardname);
        if(buyCard(buycard, &G) >= 0){
            fprintf(outs, "[Player %d] Bought %s for %d coins\n", curplayer, buycardname, getCost(buycard));
            if(V) printf("[Player %d] Bought %s for %d coins\n", curplayer, buycardname, getCost(buycard));
        }
    }

    /* End turn */
    //fprintf(outs, "[Player %d] Ending turn\n", curplayer);
    //if(V) printf("[Player %d] Ending turn\n", curplayer);
    fprintf(outs, "----------\n");
    if(V) printf("----------\n");
    endTurn(&G);
  } // end of While

  fprintf(outs, "Finished game.\n");
  if(V) printf("Finished game.\n");

  /* Print scores and winners */
  int playerNum, score[MAX_PLAYERS];
  int numPlayers = G.numPlayers;
  for(playerNum = 0; playerNum < numPlayers; playerNum++) {
    score[playerNum] = scoreFor(playerNum, &G);
    fprintf(outs, "Player %d has a score of %d\n", playerNum, score[playerNum]);
    if(V) printf("Player %d has a score of %d\n", playerNum, score[playerNum]);
  }
  int winners[MAX_PLAYERS];
  getWinners(winners, &G);
  for(playerNum = 0; playerNum < numPlayers; playerNum++) {
    if(winners[playerNum] == 1) fprintf(outs, "Player %d won!\n", playerNum);
    if(winners[playerNum] == 1) if(V) printf("Player %d won!\n", playerNum);
  }

  return 0;
}
