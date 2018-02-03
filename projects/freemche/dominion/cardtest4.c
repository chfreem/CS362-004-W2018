//  This file is intended to test the embargo card's effect in the game
//  Dominion.  It is heavily based on a file, cardtest4.c, which was
//  provided as part of the class materials.
//
//  Cheryl Freeman, freemche@oregonstate.edu
//  CS362-400, Winter 2018
//  
//  Embargo has the following functionality:
//  It costs 2 to buy.  It allows you to add an embargo token
//  to the supply card of your choice.  After that, whenever
//  a player wants to buy a card from that pile, they must also
//  gain a curse card.  The embargo card is trashed after using.
//  The player also gains two coins when purchasing it.
//  I plan on testing embargo with the following tests:
//  1--Play embargo, specifying a nonexistant supply pile to add a token to
//  2--Play embargo, specifying a supply pile which is not being used in 
//     this game
//  3--Play embargo on a supply pile, legitimately
//  4--Play embargo on a supply pile which already has am embargo token
//  5--Play embargo on a supply pile which is empty
//  After embargo is successfully played, the state of the game should
//  be unchanged except for the following:
//  a--embargoTokens for the chosen supply pile should be incremented
//  b--coins should be higher by two
//  c--handCount should be decremented (because embargo was played)
//  d--hand should no longer contain embargo
//  e--playedCardCount (which should be renamed trashedCardCount) should
//     be incremented by 1
//  f--playedCards should now hold embargo
//
//   (The numActions decrement from this card is
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

#define TESTCARD "embargo"

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
	//  embargoTokens, coins, handCount, hand, playedCardCount,
	//  and playedCards
	int checkFlags[] = {1,1,0,1,1,1,1,1,0,1,0,0,1,1,1,1,0,0};

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\nTesting use of embargo, specifying a nonsense supply pile\n");
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions

	currentState.hand[player][0] = embargo;
	int nonsenseSupplyCard = 99;

	//  Our game is set.  Let's save its "before" status.
	copyGame(&currentState, &storedState);

	result = cardEffect(embargo, nonsenseSupplyCard, 0, 0, &currentState, 0, &bonus);
	myAssert(-1, result, "cardEffect() returned a failure flag");

	return 0;
}


