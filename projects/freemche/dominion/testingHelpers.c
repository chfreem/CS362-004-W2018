#include "testingHelpers.h"
#include <stdio.h>

void myAssert(int conditionA, int conditionB, 
		char* condATitle, char* condBTitle)
{
	printf("Expected %s = %d, Actual Result %s = %d.  ",
			condATitle, conditionA,
			condBTitle, conditionB);
	if (conditionA == conditionB)
	{
		printf("Test PASSED\n");
	}
	else
	{
		printf("Test FAILED\n");
	}

	return;
}

void copyGame(struct gameState *oldGame, struct gameState *newGame)
{
	int i;	
	int j;	
	int k;
	newGame->numPlayers = oldGame->numPlayers;
	newGame->outpostPlayed = oldGame->outpostPlayed;
	newGame->outpostTurn = oldGame->outpostTurn;
	newGame->whoseTurn = oldGame->whoseTurn;
	newGame->phase = oldGame->phase;
	newGame->numActions = oldGame->numActions;
	newGame->coins = oldGame->coins;
	newGame->numBuys = oldGame->numBuys;
	newGame->playedCardCount = oldGame->playedCardCount;
	for (i=0; i < treasure_map + 1; i++)
	{
		newGame->supplyCount[i] = oldGame->supplyCount[i];
		newGame->embargoTokens[i] = oldGame->embargoTokens[i];
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		newGame->handCount[i] = oldGame->handCount[i];
		newGame->deckCount[i] = oldGame->deckCount[i];
		newGame->discardCount[i] = oldGame->discardCount[i];
		for (j = 0; j < MAX_HAND; j++)
		{
			newGame->hand[i][j] = oldGame->hand[i][j];
		}
		for (k = 0; k < MAX_DECK; k++)
		{
			newGame->deck[i][k] = oldGame->deck[i][k];
			newGame->discard[i][k] = oldGame->discard[i][k];
			newGame->playedCards[k] = oldGame->playedCards[k];
		}
	}
	return;
}

void checkStateDifferences(struct gameState *oldGame, struct gameState *newGame)
{
	return;
}
