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
//  6--choose a card to be counted that is not being used in this game
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
	int cardToCount;
	int result;		//  for storage of function return value
	int i;

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
	printf("\nplayer is higher than numPlayers\n");
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
	player = 3;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, copper, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	printf("fullDeckCount() returned a count of %d\n", result);
	printf("WARNING: THIS IS SENSIBLE-LOOKING DATA RETURNING FROM A NONSENSE FUNCTION CALL.\n");
	

	//  Test #2
	printf("\nplayer is higher than MAX_PLAYERS\n");
//	memset(&currentState, '\0', sizeof(struct gameState));
//	memset(&storedState, '\0', sizeof(struct gameState));
//	result = initializeGame(numPlayers, k, seed, &currentState); 
//	if (result < 0)
//	{
//		printf("Game initialization not successful.\n");
//		return -1;
//	}
//
//	//  Now we want to change the game state for
//	//  our testing conditions
//	player = 600;
//	copyGame(&currentState, &storedState);
//
//	//  Ready to test!
//	result = fullDeckCount(player, copper, &currentState);
//	checkStateDifferences(&storedState, &currentState, checkFlags);
//	printf("fullDeckCount() returned a count of %d\n", result);
//	printf("WARNING: THIS IS SENSIBLE-LOOKING DATA RETURNING FROM A NONSENSE FUNCTION CALL.\n");
	printf("This test sometimes causes a core dump.\n");
	


	//  Test #3
	printf("\nplayer is a negative number\n");
//	memset(&currentState, '\0', sizeof(struct gameState));
//	memset(&storedState, '\0', sizeof(struct gameState));
//	result = initializeGame(numPlayers, k, seed, &currentState); 
//	if (result < 0)
//	{
//		printf("Game initialization not successful.\n");
//		return -1;
//	}
//
//	//  Now we want to change the game state for
//	//  our testing conditions
//	player = -1;
//	copyGame(&currentState, &storedState);
//
//	//  Ready to test!
//	result = fullDeckCount(player, copper, &currentState);
//	checkStateDifferences(&storedState, &currentState, checkFlags);
//	printf("fullDeckCount() returned a count of %d\n", result);
//	printf("WARNING: THIS IS SENSIBLE-LOOKING DATA RETURNING FROM A NONSENSE FUNCTION CALL.\n");
	printf("This test sometimes causes a core dump.\n");


	//  Test #4
	printf("\ncard to count is lower than approved range\n");
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
	cardToCount = -1;
	player = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, cardToCount, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	printf("fullDeckCount() returned a count of %d\n", result);
	printf("WARNING: THIS IS SENSIBLE-LOOKING DATA RETURNING FROM A NONSENSE FUNCTION CALL.\n");

	//  Test #5
	printf("\ncard to count is higher than approved range\n");
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
	cardToCount = 27;
	player = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, cardToCount, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	printf("fullDeckCount() returned a count of %d\n", result);
	printf("WARNING: THIS IS SENSIBLE-LOOKING DATA RETURNING FROM A NONSENSE FUNCTION CALL.\n");
	


	//  Test #6
	printf("\ncard to count is not being used in this game\n");
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
	cardToCount = remodel;
	player = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, cardToCount, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(result, 0, "fullDeckCount");


	//  Test #7
	printf("\nPlayer has none of card being counted\n");
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
	cardToCount = province;
	player = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, cardToCount, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(result, 0, "fullDeckCount");


	//  Test #8
	printf("\nPlayer has some of the card being counted\n");
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
	cardToCount = copper;
	player = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, cardToCount, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(result, 7, "copper Count");


	//  Test #9
	printf("\nPlayer's deck, hand, and discard are full of the card being counted\n");
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
	cardToCount = copper;
	player = 0;
	currentState.deckCount[player] = 10;
	currentState.handCount[player] = 10;
	currentState.discardCount[player] = 10;
	for (i=0; i< currentState.deckCount[player]; i++)
	{
		currentState.deck[player][i] = copper;
	}
	for (i=0; i< currentState.handCount[player]; i++)
	{
		currentState.hand[player][i] = copper;
	}
	for (i=0; i< currentState.discardCount[player]; i++)
	{
		currentState.discard[player][i] = copper;
	}
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = fullDeckCount(player, cardToCount, &currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(result, 30, "copper Count");
	return 0;
}
