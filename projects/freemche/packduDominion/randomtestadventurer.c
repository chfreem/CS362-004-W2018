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
#include "testingHelpers.h"

int checkAdventurer(struct gameState *currentState, int handPos) 
{
	struct gameState storedState;
	memcpy (&storedState, currentState, sizeof(struct gameState));
	int player = currentState->whoseTurn;
	int problemFlag = 0;
	int i;

	adventurerEffect(currentState);
	
//  now we need to do the same thing to our storedState, as we think should have
//  been done in cardeffect to the currentState.
//  Because adventurerEffect involves a shuffle mid-point in its function,
//  it's impossible for us to follow its actions exactly unless we just copy
//  over its end state and rewind it to its immediate-post-shuffle state.
//  Instead of that, I'm only going to check the handCount, hand, discardCount,
//  and deckCount.
	//  First, check how many treasure cards are in the deck and discard
	int numTreasureCards = 0;
	numTreasureCards = numTreasureCards + 
		numSpecificCardsInDeck(&storedState, player, copper) +
		numSpecificCardsInDeck(&storedState, player, silver) +
		numSpecificCardsInDeck(&storedState, player, gold) +
		numSpecificCardsInDiscard(&storedState, player, copper) +
		numSpecificCardsInDiscard(&storedState, player, silver) +
		numSpecificCardsInDiscard(&storedState, player, gold); 

	if (numTreasureCards == 0)
	{
		//  The hand should be moved down by one card (the adventurer), 
		//  the deck should be empty,
		//  and the discard should have all the deck's cards in it
		//  plus the played adventurer card
		for (i = 0; i < currentState->handCount[player]; i++)
		{
			if (currentState->hand[player][i] != storedState.hand[player][i] + 1)
			{
				problemFlag = 1;
				printf("0 treasure cards, cards should be moved down in hand but are not\n");
			}
		}
		if (currentState->deckCount[player] != 0)
		{
			problemFlag = 1;
			printf("0 treasure cards, deckCount should be zero but is not\n");
		}
		if (currentState->discardCount[player] != (storedState.discardCount[player] + storedState.deckCount[player]))
		{
			problemFlag = 1;
			printf("0 treasure cards, all cards should be in discard but are not\n");
		}
	}
	else if (numTreasureCards == 1)
	{
		//  The hand should have one extra treasure card in it,
		//  but one less adventurer in it,
		//  the deck should be empty, and the discard should
		//  have all the deck's cards in it plus the played adventurer card
		int storedStateHandTreasureCardNum = numSpecificCardsInHand(&storedState, player, copper) +
				numSpecificCardsInHand(&storedState, player, silver) +
				numSpecificCardsInHand(&storedState, player, gold);
		int currentStateHandTreasureCardNum = numSpecificCardsInHand(currentState, player, copper) +
				numSpecificCardsInHand(currentState, player, silver) +
				numSpecificCardsInHand(currentState, player, gold);
		if (currentStateHandTreasureCardNum != (storedStateHandTreasureCardNum + 1))
		{
			problemFlag = 1;
			printf("1 treasure card, but one treasure card was not added to hand\n");
		}
		if (currentState->handCount[player] != storedState.handCount[player])
		{
			problemFlag = 1;
			printf("1 treasure card, but handCount doesn't reflect adding it and subtracting the played adventurer card\n");
		}
		if (currentState->deckCount[player] != 0)
		{
			problemFlag = 1;
			printf("1 treasure card, but the deck is not empty\n");
		}
		if (currentState->discardCount[player] != (storedState.discardCount[player] + storedState.deckCount[player] + 1))
		{
			problemFlag = 1;
			printf("1 treasure card, but discard doesn't have all cards from deck in it plus the played adventurer card\n");
		}
	}
	else
	{
		//  numTreasureCards is 2 or higher
		//  The hand should have two extra treasure cards in it,
		//  one less adventurer card in it,
		//  the deck plus discard should have two fewer cards from putting treasure cards into hand
		//  but one more card from the played adventurer card
		int storedStateHandTreasureCardNum = numSpecificCardsInHand(&storedState, player, copper) +
				numSpecificCardsInHand(&storedState, player, silver) +
				numSpecificCardsInHand(&storedState, player, gold);
		int currentStateHandTreasureCardNum = numSpecificCardsInHand(currentState, player, copper) +
				numSpecificCardsInHand(currentState, player, silver) +
				numSpecificCardsInHand(currentState, player, gold);
		if (currentStateHandTreasureCardNum != (storedStateHandTreasureCardNum + 2))
		{
			problemFlag = 1;
			printf(">=2 treasure cards, but 2 have not been added to hand\n");

//				printf("currentStateHandTreasureCardNum = %d, storedStateHandTreasureCardNum = %d\n", currentStateHandTreasureCardNum, storedStateHandTreasureCardNum);
		}
		if (currentState->handCount[player]  != (storedState.handCount[player] + 1))
		{
			problemFlag = 1;
			printf(">=2 treasure cards, but handCount is not (+2 treas, -1 advent)\n");
		}
		if ((currentState->discardCount[player] + currentState->deckCount[player])  != (storedState.discardCount[player] + storedState.deckCount[player] - 1))
		{
			problemFlag = 1;
			printf(">=2 treasure cards, but combined deck and discard are not down by 1 (-2 treas, +1 advent)\n");
		}
	}
	//  Now that all the specific changes have been logged, I'll do one
	//  more check to see if anything unexpected has changed about the
	//  game state.  I don't expect that this will print out anything, but
	//  it can be checked for in the output file.
	int checkFlags[] = {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};	
	checkStateDifferences(&storedState, currentState, checkFlags);

	return problemFlag;
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
