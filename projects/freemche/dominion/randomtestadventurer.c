//  This is an automated random test generator for the dominion card Adventurer
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

int checkAdventurer(struct gameState *currentState, int handPos) 
{
	struct gameState storedState;
	memcpy (&storedState, currentState, sizeof(struct gameState));
	int player = currentState->whoseTurn;

	adventurerEffect(currentState);
	
//  now we need to do the same thing to our storedState, as we think should have
//  been done in cardeffect to the currentState.
//  Because adventurerEffect involves a shuffle mid-point in its function,
//  it's impossible for us to follow its actions exactly unless we just copy
//  over its end state and rewind it to its immediate-post-shuffle state.
//  Instead of that, I'm only going to check the handCount, hand, discardCount,
//  and deckCount.
	int tempHand[MAX_HAND];

	int z=0;	//  the counter for the temp hand
	int drawnTreasure = 0;
	int cardDrawn;
	while ((drawnTreasure < 2) || ((storedState.deckCount[player] + storedState.discardCount[player]) != 0))
	{
		if (storedState
		drawCard(player, &storedState);
		cardDrawn = storedState.hand[player][storedState


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

	printf ("Testing Adventurer\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 20; n++) {		//  The number of random tests we'll run
		//  Not sure why "256" in the next statement, but it worked
		//  for Dr. Groce so I'll keep it.
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		
		//  Now our game struct is filled with completely random
		//  stuff that doesn't make any sense at all.  Let's put some
		//  sensible stuff in the parts that will be used by
		//  our function under test
		//  Adventurer causes the player to cycle through their deck
		//  until either they find 2 treasure cards, or they go through
		//  their entire deck/discard combo and only find 1 treasure card
		//  or 0 treasure cards.  The 1 or 2 treasure cards are added to the
		//  player's hand, and the revealed cards are added to the 
		//  discard.
		player = floor(Random() * 2);		//  Only 0, 1 players allowed
		G.whoseTurn = player;
		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);
		G. playedCardCount = floor(Random() * MAX_DECK);

		//  I'm going to fill each of the deck, hand, and discard with
		//  legitimate cards (though not necessarily cards which are
		//  being used in some fictictious game)
		for (i=0; i<G.deckCount[player]; i++)
		{
			G.deck[player][i] = floor(Random() * (treasure_map + 1));
		}
		for (i=0; i<G.discardCount[player]; i++)
		{
			G.discard[player][i] = floor(Random() * (treasure_map + 1));
		}
		for (i=0; i<G.handCount[player]; i++)
		{
			G.hand[player][i] = floor(Random() * (treasure_map + 1));
		}
		for (i=0; i<G.playedCardCount; i++)
		{
			G.playedCards[i] = floor(Random() * (treasure_map + 1));
		}
					
		//  I'm going to specify that the Great Hall card played is
		//  always in position 0 in the hand.  
		handPos = 0;
		G.hand[player][handPos] = adventurer;


//		printf("n=%d, player=%d, G.deckCount=%d, G.discardCount=%d, G.handCount=%d\n", n, player, G.deckCount[player], G.discardCount[player], G.handCount[player]);
		result = checkAdventurer(&G, handPos);
		if (result)
		{
			printf("problem with test results, case n = %d\n", n);
		}
	}


	return 0;
}
