//  ***********************************************************************  //
//  This is written as part of Assignment 3 in CS362-400, Winter 2018.
//  Author:  Cheryl Freeman, freemche@oregonstate.edu
//
//  This is written to test the function "isGameOver" in the file dominion.c
//
//  This unit test is based on code given to us as part of the class
//  materials, in the file testUpdateCoins.c.  I especially appreciated the
//  help with the memcpy lines and the memset reminder.
//
//  The tests I plan on running for isGameOver()  are:
//  1--0 province cards
//  --nonzero province cards and...
//  2--every supply card is gone
//  3--the last 3 supply cards checked are gone
//  4--the last 2 supply cards checked are gone
//  ***********************************************************************  //
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testingHelpers.h"
#include "rngs.h"
#define TESTFUNCTION "shuffle(), unittest1.c"

int main()
{
	int seed = 20;		//  for random function
	int numPlayers = 2;
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

	printf("\n-------------------------------------------------------\n");
	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);


	//  Test #1
	printf("\nProvince cards are gone\n");
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
	currentState.supplyCount[province] = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = isGameOver(&currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(1, result,"isGameOver");
	


	//  Test #2
	printf("\nEvery supply card except province is gone\n");
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
	currentState.supplyCount[province] = 10;
	for (i=curse; i<treasure_map+1; i++)
	{
		if (i != province)
		{
			if (currentState.supplyCount[i] != -1)
			{	//  the card was used in the game
				currentState.supplyCount[i] = 0;
			}
		}
	}
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = isGameOver(&currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(1, result,"isGameOver");
	

	//  Test #3
	printf("\nThe last 3 supply cards checked are gone\n");
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
	currentState.supplyCount[province] = 10;
	currentState.supplyCount[sea_hag] = 0;
	currentState.supplyCount[embargo] = 0;
	currentState.supplyCount[cutpurse] = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = isGameOver(&currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(1, result,"isGameOver");
	

	//  Test #4
	printf("\nThe last 2 supply cards checked are gone\n");
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
	currentState.supplyCount[province] = 10;
	currentState.supplyCount[sea_hag] = 0;
	currentState.supplyCount[embargo] = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = isGameOver(&currentState);
	checkStateDifferences(&storedState, &currentState, checkFlags);
	myAssert(0, result,"isGameOver");
	return 0;
}
