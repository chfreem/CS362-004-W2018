//  ***********************************************************************  //
//  This is written as part of Assignment 3 in CS362-400, Winter 2018.
//  Author:  Cheryl Freeman, freemche@oregonstate.edu
//
//  This is written to test the function "buyCard()" in the file dominion.c
//  It uses an assertion function instead of assert() so that the program
//  will not crash when it fails a test.  This way, output can be printed
//  and we can have a better idea of where the test failed.
//
//  This unit test is based on code given to us as part of the class
//  materials, in the file testUpdateCoins.c.  I especially appreciated the
//  help with the memcpy lines and the memset reminder.
//
//  The tests I plan on running for buyCard() are:
//  1--if player wants to buy, but they don'thave any buys left
//  2--if player wants to buy a certain card, but there aren't any left
//  3--if player wants to buy a card they don't have the money for
//  4--if somehow an invalid supplyPos is sent as an argument to buyCard()
//  5--if player is in the clean-up phase, but they want to buy something
//  6--if player wants to buy a card which is not being used in this game
//  7--if player makes a valid buy
//  8--if player wants to buy a card which has an embargo token on it
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

	//  Test # 1:  player wants to buy, but they don't have enough buys
	printf("Trying to buy without any numBuys:\n");	
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
	currentState.numBuys = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = buyCard(0, &currentState);
	if (result < 0)
	{
		checkStateDifferences(&currentState, &storedState,
				checkFlags);
		printf("Unable to buy when numBuys = 0.  PASSED.\n");
	}
	else
	{
		printf("buyCard() returned successfully when it");
		printf(" should have failed because numBuys = 0\n");
	}
	
	
	//  Test # 2:  player wants to buy a card that has run out
	printf("Trying to buy a card that has run out:\n");	
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
	//  I'll say that there are no duchy cards left
	currentState.supplyCount[2] = 0;
	copyGame(&currentState, &storedState);

	//  Ready to test!
	result = buyCard(2, &currentState);
	if (result < 0)
	{
		checkStateDifferences(&currentState, &storedState,
				checkFlags);
		printf("Unable to buy when quantity desired card = 0.  PASSED.\n");
	}
	else
	{
		printf("buyCard() returned successfully when it");
		printf(" should have failed because qty desired card = 0\n");
	}
	


	//  Test # 3
	printf("Trying to buy a card when I don't have enough cash:\n");	
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
	currentState.coins= 2;
	copyGame(&currentState, &storedState);

	//  Ready to test!  I'm going to try to buy a duchy card,
	//  which costs 5, when I only have 2 coins.
	result = buyCard(2, &currentState);
	if (result < 0)
	{
		checkStateDifferences(&currentState, &storedState,
				checkFlags);
		printf("Unable to buy when I don't have enough money.  PASSED.\n");
	}
	else
	{
		printf("buyCard() returned successfully when it");
		printf(" should have failed because I didn't have enough money\n");
	}
	return 0;
}
