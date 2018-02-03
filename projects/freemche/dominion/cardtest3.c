//  This file is intended to test the mine card's effect in the game
//  Dominion.  It is heavily based on a file, cardtest4.c, which was
//  provided as part of the class materials.
//
//  Cheryl Freeman, freemche@oregonstate.edu
//  CS362-400, Winter 2018
//  
//  Mine has the following functionality:
//  It costs 5 to buy.  It allows you to trash a treasure from
//  your hand and get a treasure card to your hand that is
//  an upgraded version (trash a copper, gain a silver; trash
//  a silver, gain a gold).
//  To test the functionality of Mine, I will check the following:
//  1--Mine when there are no treasure cards of the "upgrade" type
//     in the supply
//  2--Mine when there are no treasure cards in the player's hand
//  3--Mine when the player has a treasure card and there is
//     an upgrade available
//  4--Mine when the player has a treasure card and they choose
//     a treasure card that's the same value
//  5--The player specifies a non-treasure card to trash and
//     upgrade.
//  6--The card they want to upgrade to isn't a valid card
//  7--The card they want to upgrade to costs too much
//  The things to check after this are:
//  a--supplyCount
//  b--hand
//  c--handCount
//  f--playedCards
//  g--playedCardCount
//
//   (The numActions decrement and the coins addition from this card are
//   carried out in playCard(), which is not being tested with this
//   unit test.)

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "testingHelpers.h"

#define TESTCARD "mine, cardtest3.c"

int main() {
	int seed = 20;
	int numPlayers = 2;
	int player = 0;
	int i;
	int bonus = 0;
	int result;		//  For storing result of function calls

	//  I'm using the same cards as in playdom.c
	int k[10] = {adventurer, gardens, embargo, village, minion, mine,
			cutpurse, sea_hag, tribute, smithy};
	struct gameState currentState;
	struct gameState storedState;	//  For comparison to see if changes
					//  were made
	//  The following array tells the checkStateDifferences()
	//  function which components of the game state should be
	//  checked.  In this case, we don't want to check the
	//  deck, deckCount, hand, and handCount.
	//  also supplyCount
	//  Also, playedCard and playedCardCount
	//  we'll check them more specifically below).
	int checkFlags[] = {1,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0};

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\nTesting use of Mine when there are no upgrade coins in Supply\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	currentState.hand[player][0] = mine;
	currentState.supplyCount[silver] = 0;
	currentState.hand[player][1] = copper;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(mine, copper, silver, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	myAssert(storedState.supplyCount[player], currentState.supplyCount[player], "supplyCount unchanged");
	myAssert(storedState.handCount[player]-1, currentState.handCount[player], "handCount down by one");
	myAssert(storedState.playedCardCount+1, currentState.playedCardCount, "playedCardCount");
	myAssert(mine, currentState.playedCards[currentState.playedCardCount-1], "mine is in playedCards");



	printf("\nTesting use of Mine when there is no treasure card in player's hand\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	for (i=0; i<currentState.handCount[player]; i++)
	{
		currentState.hand[player][i] = mine;
	}

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(mine, copper, silver, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	myAssert(storedState.supplyCount[player], currentState.supplyCount[player], "supplyCount unchanged");
	myAssert(storedState.handCount[player]-1, currentState.handCount[player], "handCount down by one");
//	myAssert(1, ((currentState.hand[player][currentState.handCount[player]-1] == gold)
//			&& (currentState.hand[player][currentState.handCount[player]-2] == gold)
//			&& (currentState.hand[player][currentState.handCount[player]-3] == gold)),
//			"the cards from the deck are in the hand now");
	myAssert(storedState.playedCardCount+1, currentState.playedCardCount, "playedCardCount");
	myAssert(mine, currentState.playedCards[currentState.playedCardCount-1], "mine is in playedCards");

	return 0;
}


