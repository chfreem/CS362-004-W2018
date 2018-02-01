//  ***********************************************************************  //
//  This is written as part of Assignment 3 in CS362-400, Winter 2018.
//  Author:  Cheryl Freeman, freemche@oregonstate.edu
//
//  This is written to test the function "fullDeckCount()" in the file dominion.c
//
//  This unit test is based on code given to us as part of the class
//  materials, in the file testUpdateCoins.c.  I especially appreciated the
//  help with the memcpy lines and the memset reminder.
//
//  The tests I plan on running for fullDeckCount()  are:
//  1--specify a player that is higher than numPlayers
//  2--specify a player that is higher than MAX_PLAYERS
//  3--specify a player that is lower than 0
//  4--choose a card to be counted that is lower than the allowed range
//  5--choose a card to be counted that is higher than the allowed range
//  6--choose a card to be counted that is not eing used in this game
//  7--choose a card to be used, but that player doesn't possess any
//  8--choose a card that is being used, and that player owns some
//  9--fill the player's deck, hand, and discard all with the card to be
//     counted
//  10-Achieve loop coverage by running each of the 3 loops 0, 1, and 2 times
//  ***********************************************************************  //
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testingHelpers.h"
#include "rngs.h"

int main()
{
	int seed = 20;		//  for random function
	int numPlayers = 2;
	int player;
	int result;		//  for storage of function return value

	//  I'm using the same cards as in playdom.c
	int k[10] = {adventurer, gardens, embargo, village, minion, mine,
			cutpurse, sea_hag, tribute, smithy};
	struct gameState currentState;
	struct gameState storedState;	//  For comparison to see if changes
					//  were made
	//  The following array tells the checkStateDifferences()
	//  function which components of the game state should be
	//  checked.  
	int checkFlags[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	//  Test #1
	printf("player is higher than numPlayers\n");
	memset(&currentState, '\0', sizeof(struct gameState));
	memset(&storedState, '\0', sizeof(struct gameState));
	result = initializeGame(numPlayers, k, seed, &currentState); 
	if (result < 0)
	{
		printf("Game initialization not successful.\n");
		return -1;
	}

	//  Now we want to change the game state for
	//  our testing conditions
	player = 893;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, copper, &currentState);
	printf("fullDeckCount() returned a count of %d\n", result);
	return 0;
}
