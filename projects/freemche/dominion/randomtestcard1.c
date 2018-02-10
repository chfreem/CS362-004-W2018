//  This is an automated random test generator for the dominion card Embargo.
//  It is strongly based on the example file distributed as part of the
//  class materials in the file testDrawCard.c, which was possibly
//  written by Alex Groce of Oregon State University.
//
//  Cheryl Freeman, freemche@oregonstate.edu
//  CS362-400, Winter 2018
//
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int checkEmbargo(int intendedPile, struct gameState *currentState, int handPos) 
{
	struct gameState storedState;
	memcpy (&storedState, currentState, sizeof(struct gameState));

	int result;		//  Stores the result of function calls

	result = embargoEffect(intendedPile, currentState, handPos);

//  Now we need to do the same thing to our storedState, as we think should have
//  been done in embargoEffect to the currentState.
	storedState.coins = storedState.coins + 2;
	if (storedState.supplyCount[intendedPile] != -1)
	{
		storedState.embargoTokens[estate]++;
	}
	
	if ((storedState.coins == currentState->coins)
			&& storedState.embargoTokens[estate] == currentState->embargoTokens[estate])
	{
		return 0;
	}
	else
	{
//		printf("intendedPile = %d, storedState.coins = %d, currentState->coins = %d, storedState.embargoTokens[estate] = %d, currentState->embargoTokens[estate] = %d\n", intendedPile, storedState.coins, currentState->coins, storedState.embargoTokens[estate], currentState->embargoTokens[estate]);
		return -1;
	}

		
	//	The following commented-out lines should be good to test
	//	this, if the discardCard function is working OK.  Since it
	//	is not, I will only use this test to check the coins and
	//	embargo tokens and nothing else about the state.
//	discardCard(handPos, storedState.whoseTurn, &storedState, 1);

//	if (!memcmp(&storedState, currentState, sizeof(struct gameState)))
//	{		//  They are the same
//		return 0;
//	}
//	else
//	{
//		return -1;
//	}
}

int main () {

	//  int i, n, result, p, deckCount, discardCount, handCount;

	//  I'm using the same piles as used in playdom.c
//	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
//		sea_hag, tribute, smithy};
	int i;
	int player;
	struct gameState G;
	int n;			//  number of tests to be run
	int intendedPile;	//  The pile upon which to place embargo token
	int handPos;		//  The location of the embargo card in player's hand
	int result;		//  stores result of function call

	printf ("Testing embargoEffect\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 20000; n++) {		//  The number of random tests we'll run
		//  Not sure why "256" in the next statement, but it worked
		//  for Dr. Groce so I'll keep it.
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		
		//  Now our game struct is filled with completely random
		//  stuff that doesn't make any sense at all.  Let's put some
		//  sensible stuff in the parts that will be used by
		//  our function under test
		player = floor(Random() * 2);		//  Only 0, 1 players allowed
		G.whoseTurn = player;

		//  I want the supplyCount of the chosen pile to be either
		//  0, which means the pile is empty
		//  1, which means there's a card there to put an embargo Token on
		//  -1, which means that pile is not used in the game
		//  I'm always going to have the embargo test run on the estate
		//  card
		int randomNum = Random()*3;
		if (randomNum == 0)
		{
			G.supplyCount[estate] = 0;
		}
		else if (randomNum == 1)
		{
			G.supplyCount[estate] = 1;
		}
		else if (randomNum == 2)
		{
			G.supplyCount[estate] = -1;
		}

		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);
		G.playedCardCount = floor(Random() * MAX_DECK);
		intendedPile = estate;
		//  I'm going to specify that the embargo card played is
		//  always in position 0 in the hand.  Not specifying this
		//  would break discardCard(), when what I really want to test is
		//  embargoEffect.
		handPos = 0;
		G.hand[player][handPos] = embargo;


//		printf("n=%d, player=%d, G.supplyCount[estate]=%d, G.deckCount=%d, G.discardCount=%d, G.handCount=%d\n", n, player, G.supplyCount[estate], G.deckCount[player], G.discardCount[player], G.handCount[player]);
		result = checkEmbargo(intendedPile, &G, handPos);
		if (result)
		{
			printf("problem with test results, case n = %d\n", n);
		}
	}


	return 0;
}
