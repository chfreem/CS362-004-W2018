//  ***********************************************************************  //
//  This is written as part of Assignment 3 in CS362-400, Winter 2018.
//  Author:  Cheryl Freeman, freemche@oregonstate.edu
//
//  This is written to test the function "shuffle()" in the file dominion.c
//  It uses an assertion function instead of assert() so that the program
//  will not crash when it fails a test.  This way, output can be printed
//  and we can have a better idea of where the test failed.
//
//  This unit test is based on code given to us as part of the class
//  materials, in the file testUpdateCoins.c.  I especially appreciated the
//  help with the memcpy lines and the memset reminder.
//  ***********************************************************************  //
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"

int main()
{
	int i;		//  loop counter
	int seed = 20;	//  for random function
	int numPlayers = 2;	//  we'll test for up to this number of players
	int negativePlayers = -1;	//  This ought to break the function
	int player;	//  loop counter
	int tooBigDeckSize = MAX_DECK + 1;
	int negativeDeckSize = -1;
	int numCardsInDeck;

	//  I'm using the same cards as in playdom.c
	int k[10] = {adventurer, gardens, embargo, village, minion, mine,
			cutpurse, sea_hag, tribute, smithy};
	struct gameState currentState;

	//  I'm going to test the shuffling function when the player's
	//  entire deck is full of identical cards
	int identicalCards[MAX_DECK];
	for (i=0; i < MAX_DECK; i++)
	{
		identicalCards[i] = copper;
	}

	//  I'm also going to test the shuffling function when there are no
	//  cards which are the same, in the player's deck
	int differentCards[MAX_DECK];
	for (i=0; i < MAX_DECK; i++)
	{
		differentCards[i] = i;
	}

	for (p = negativePlayers; p < numPlayers; p++)
	{
		for  (numCardsInDeck = negativeDeckSize;
			numCardsInDeck < tooBigDeckSize;
			numCardsInDeck++)
		{
			printf("Test player %d with %d cards:  \n", p, numCardsInDeck);

			//  Clear out the previous game state
			memset(&currentState, '\0', sizeof(struct gameState));
			initialize

	myAssert(2, 1, "firstNum", "secondNum");

	return 0;
}

