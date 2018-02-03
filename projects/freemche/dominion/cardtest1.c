//  This file is intended to test the adventurer card's effect in the game
//  Dominion.  It is heavily based on a file, cardtest4.c, which was
//  provided as part of the class materials.
//
//  Cheryl Freeman, freemche@oregonstate.edu
//  CS362-400, Winter 2018
//  
//  Adventurer has the following functionality:
//  It costs 6 to buy.  When you use it, you go through your deck,
//  revealing cards and setting them aside (not into the discard until
//  you need to shuffle) until you have found two treasure cards.  These
//  treasure cards go into your hand.  Then you put the revealed cards
//  into your discard pile.
//  To test the functionality of Adventurer, I will check the following:
//  1--no treasure cards in your deck
//  2--1 treasure card in your deck
//  3--2 treasure cards in your deck, at the end of the deck
//  4--many treasure cards in your deck
//  5--post test 3 or 4, which should function successfully, I will
//     check that the game state is the same, except for the following
//     expected changes:
//     a--handCount higher by 2
//     b--hand contains the 2 treasure cards added on the back
//     c--deckCount is smaller by the number of revealed cards
//     d--deck does not contain the revealed cards anymore
//     e--discardCount is higher by the number of discarded cards
//     f--discard contains the discarded cards
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

#define TESTCARD "adventurer, cardtest1.c"

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
	//  deck (we know it has changed from the shuffling, and
	//  we'll check it more specifically below).
	int checkFlags[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1};

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\nTesting with no treasure cards in the deck\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	for (i=0; i<currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = curse;
	}
	currentState.hand[player][0] = adventurer;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(adventurer, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	printf("\nTesting with one treasure card\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	for (i=0; i<currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = curse;
	}
	currentState.hand[player][0] = adventurer;
	currentState.deck[player][currentState.deckCount[player] - 1] = gold;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(adventurer, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	printf("\nTesting with 2 treasure cards in the deck, at the end of the deck\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	for (i=0; i<currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = curse;
	}
	currentState.hand[player][0] = adventurer;
	currentState.deck[player][currentState.deckCount[player] - 1] = gold;
	currentState.deck[player][currentState.deckCount[player] - 2] = gold;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(adventurer, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);

	printf("\nTesting with the entire deck made of treasure cards\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	for (i=0; i<currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = gold;
	}
	currentState.hand[player][0] = adventurer;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	cardEffect(adventurer, 0, 0, 0, &currentState, 0, &bonus);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(storedState.handCount[player]+2, currentState.handCount[player], "handCount");
	myAssert(1, ((currentState.hand[player][currentState.handCount[player]-1] == gold)
			&& (currentState.hand[player][currentState.handCount[player]-2] == gold)),
			"last two cards in hand are treasure cards");
	myAssert(storedState.deckCount[player]-2,currentState.deckCount[player], "deckCount smaller by the number of revealed cards");
//     d--deck does not contain the revealed cards anymore
	//  I won't check this.  To check this, I'd have to have the deck
	//  contain only two treasure cards so that I could tell if they
	//  had been removed.  I could insert this test up above where I'm
	//  testing that deck condition, but I'll not do it on this iteration
	//  of testing.
	myAssert(storedState.discardCount[player], storedState.discardCount[player], "discardCount is higher by the number of discarded cards");
//     f--discard contains the discarded cards
//     Again, I won't test this now.  I would need to insert this test up
//     above, where the entire deck is not made up of treasure cards.  I'll
//     do this on a future iteration of testing, if it needs to be done.
	return 0;
}


