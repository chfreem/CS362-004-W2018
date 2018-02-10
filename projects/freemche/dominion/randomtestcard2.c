//  This is an automated random test generator for the dominion card Great Hall.
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
#include "rngs.h"
#include <math.h>

int checkGreatHall(struct gameState *currentState, int handPos) 
{
	struct gameState storedState;
	memcpy (&storedState, currentState, sizeof(struct gameState));
	int result;		//  stores the result of function calls

	int cardToPlay = great_hall;
	int choice1, choice2, choice3;
	choice1 = choice2 = choice3 = 0;
	int bonus = 0;
	int player = currentState->whoseTurn;
//	printf("cardToPlay = %d, choice1 = %d, choice2 = %d, choice3 = %d, currentState->hand[player][0] = %d, handPos = %d, bonus = %d\n", cardToPlay, choice1, choice2, choice3, currentState->hand[player][0], handPos, bonus);
	result = cardEffect(cardToPlay, choice1, choice2, choice3, currentState, handPos, &bonus);
//  now we need to do the same thing to our storedState, as we think should have
//  been done in cardeffect to the currentState.
	storedState.numActions = storedState.numActions + 1;
	
	//  i want to draw a card for the stored state, but this might
	//  require shuffling the discard in order for there to be cards to draw.
	//  i would be unable to compare the stored and current states if i
	//  merely called "drawcard", because the different shuffling would introduce
	//  differences between them.  instead, i will follow the method in
	//  testdrawcard and check if the deck has cards in it.  if it does,
	//  then i'll draw a card.  if it doesn't, i'll copy the current state's
	//  deck and discard to the stored state and then draw a card.
	if (storedState.deckCount[player] > 0) {
		storedState.handCount[player]++;
		storedState.hand[player][storedState.handCount[player]-1] = storedState.deck[player][storedState.deckCount[player]-1];
		storedState.deckCount[player]--;
	} else if (storedState.discardCount[player] > 0) {
		//  There were no cards in the storedState's deck
		memcpy(storedState.deck[player], currentState->deck[player], sizeof(int) * storedState.discardCount[player]);
		memcpy(storedState.discard[player], currentState->discard[player], sizeof(int)*storedState.discardCount[player]);
		storedState.hand[player][currentState->handCount[player]-1] = currentState->hand[player][currentState->handCount[player]-1];
		storedState.handCount[player]++;
		storedState.deckCount[player] = storedState.discardCount[player]-1;
		storedState.discardCount[player] = 0;
	}

		
	//	I'll just call discardCard() on the stored State, because I'm
	//	not testing that function.  There aren't problems with the
	//	mere discarding of a card.
	discardCard(handPos, storedState.whoseTurn, &storedState, 0);

	if (!memcmp(&storedState, currentState, sizeof(struct gameState)))
	{		//  They are the same
		return 0;
	}
	else
	{
//		printf("storedState.numActions = %d, currentState->numActions = %d, \n", storedState.numActions, currentState->numActions);
		return -1;
	}
}

int main () {

	int i;
	int player;
	struct gameState G;
	int n;			//  number of tests to be run
	int handPos;		//  The location of the Great Hall card in player's hand
	int result;		//  stores result of function call

	printf ("Testing cardEffect's case great_hall.\n");

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
		//  Great Hall causes the player to draw a card, so their
		//  hand changes, their deck changes,  and also gives them an action.
		player = floor(Random() * 2);		//  Only 0, 1 players allowed
		G.whoseTurn = player;
		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);
		G. playedCardCount = floor(Random() * MAX_DECK);
		//  I'm going to specify that the Great Hall card played is
		//  always in position 0 in the hand.  Not specifying this
		//  would break discardCard(), when what I really want to test is
		//  the great_hall case of cardEffect()
		handPos = 0;
		G.hand[player][handPos] = great_hall;


//		printf("n=%d, player=%d, G.deckCount=%d, G.discardCount=%d, G.handCount=%d\n", n, player, G.deckCount[player], G.discardCount[player], G.handCount[player]);
		result = checkGreatHall(&G, handPos);
		if (result)
		{
			printf("problem with test results, case n = %d\n", n);
		}
	}


	return 0;
}
