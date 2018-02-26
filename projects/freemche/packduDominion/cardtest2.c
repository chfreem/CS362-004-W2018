//  This file is intended to test the smithy card's effect in the game
//  Dominion.  It is heavily based on a file, cardtest4.c, which was
//  provided as part of the class materials.
//
//  Cheryl Freeman, freemche@oregonstate.edu
//  CS362-400, Winter 2018
//  
//  Smithy has the following functionality:
//  It costs 4 to buy.  It allows you to draw 3 cards from your
//  deck and add them to your hand.
//  To test the functionality of Smithy, I will check the following:
//  1--player's hand has three additional cards
//  2--player's deck is three cards smaller
//  3--The cards which were in the deck are now the cards in the hand
//  4--No other changes should occur to the game state
//
//  To try to break Smithy, I will check what happens when
//  5--player's deck had no cards, so they can't gain any
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

#define TESTCARD "smithy, cardtest2.c"

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
	//  Also, playedCard and playedCardCount
	//  we'll check them more specifically below).
	int checkFlags[] = {1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0};

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\nTesting normal use of Smithy, with no problems\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	currentState.hand[player][0] = smithy;
	for (i=0; i<currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = gold;
	}

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(smithy, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	myAssert(storedState.handCount[player]+2, currentState.handCount[player], "handCount higher by 2 (played 1, gained 3)");
	myAssert(1, ((currentState.hand[player][currentState.handCount[player]-1] == gold)
			&& (currentState.hand[player][currentState.handCount[player]-2] == gold)
			&& (currentState.hand[player][currentState.handCount[player]-3] == gold)),
			"the cards from the deck are in the hand now");
	myAssert(storedState.deckCount[player]-3,currentState.deckCount[player], "deckCount is smaller by 3");
	myAssert(storedState.playedCardCount+1, currentState.playedCardCount, "playedCardCount");
	myAssert(smithy, currentState.playedCards[currentState.playedCardCount-1], "smithy is in playedCards");


	printf("\nTesting smithy when deck has no cards in it\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	currentState.hand[player][0] = smithy;
	currentState.deckCount[player] = 0;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(smithy, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	myAssert(storedState.handCount[player]-1, currentState.handCount[player], "handCount is one smaller");
	myAssert(storedState.deckCount[player],currentState.deckCount[player], "deckCount unchanged");
	myAssert(storedState.playedCardCount+1, currentState.playedCardCount, "playedCardCount");
	myAssert(smithy, currentState.playedCards[currentState.playedCardCount-1], "smithy is in playedCards");



	printf("\nTesting smithy when deck has two cards in it\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	currentState.hand[player][0] = smithy;
	currentState.deckCount[player] = 2;
	for (i=0; i<currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = gold;
	}

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(smithy, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	myAssert(storedState.handCount[player]+1, currentState.handCount[player], "handCount higher by 1 (played 1, gained 2)");
	myAssert(1, ((currentState.hand[player][currentState.handCount[player]-1] == gold)
			&& (currentState.hand[player][currentState.handCount[player]-2] == gold)),
			"the cards from the deck are in the hand now");
	myAssert(storedState.deckCount[player]-2,currentState.deckCount[player], "deckCount is smaller by 2");
	myAssert(storedState.playedCardCount+1, currentState.playedCardCount, "playedCardCount");
	myAssert(smithy, currentState.playedCards[currentState.playedCardCount-1], "smithy is in playedCards");

	return 0;
}
