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

void checkStateDifferences(struct gameState *oldGame, struct gameState *newGame, int checkMemberFlags[NUM_GAMESTATE_MEMBERS])
{
	int i, j;
	if (checkMemberFlags[0])
	{
		if (changed(oldGame->numPlayers, newGame->numPlayers))
		{
			printf("numPlayers has changed\n");
		}
	}
	if (checkMemberFlags[1])
	{
		for (i=0; i<treasure_map + 1; i++)
		{
			if (changed(oldGame->supplyCount[i], newGame->supplyCount[i]))
			{
				printf("supplyCount[%d] has changed\n", i);
			}
		}
	}
	if (checkMemberFlags[2])
	{
		for (i=0; i<treasure_map + 1; i++)
		{
			if (changed(oldGame->embargoTokens[i], newGame->embargoTokens[i]))
			{
				printf("embargoTokens[%d] has changed\n", i);
			}
		}
	}
	if (checkMemberFlags[3])
	{
		if (changed(oldGame->outpostPlayed, newGame->outpostPlayed))
		{
			printf("outpostPlayed has changed\n");
		}
	}
	if (checkMemberFlags[4])
	{
		if (changed(oldGame->outpostTurn, newGame->outpostTurn))
		{
			printf("outpostTurn has changed\n");
		}
	}
	if (checkMemberFlags[5])
	{
		if (changed(oldGame->whoseTurn, newGame->whoseTurn))
		{
			printf("whoseTurn has changed\n");
		}
	}
	if (checkMemberFlags[6])
	{
		if (changed(oldGame->phase, newGame->phase))
		{
			printf("phase has changed\n");
		}
	}
	if (checkMemberFlags[7])
	{
		if (changed(oldGame->numActions, newGame->numActions))
		{
			printf("numActions has changed\n");
		}
	}
	if (checkMemberFlags[8])
	{
		if (changed(oldGame->coins, newGame->coins))
		{
			printf("coins has changed\n");
		}
	}
	if (checkMemberFlags[9])
	{
		if (changed(oldGame->numBuys, newGame->numBuys))
		{
			printf("numBuys has changed\n");
		}
	}
	if (checkMemberFlags[10])
	{
		for (i=0; i<MAX_PLAYERS; i++)
		{
			for (j=0; j<MAX_HAND; j++)
			{
				if (changed(oldGame->hand[i][j], newGame->hand[i][j]))
				{
					printf("hand[%d][%d] has changed\n", i, j);
				}
			}
		}
	}
	if (checkMemberFlags[11])
	{
		for (i=0; i<MAX_PLAYERS; i++)
		{
			if (changed(oldGame->handCount[i], newGame->handCount[i]))
			{
				printf("handCount[%d] has changed\n", i);
			}
		}
	}
	if (checkMemberFlags[12])
	{
		for (i=0; i<MAX_PLAYERS; i++)
		{
			for (j=0; j<MAX_DECK; j++)
			{
				if (changed(oldGame->deck[i][j], newGame->deck[i][j]))
				{
					printf("deck[%d][%d] has changed\n", i, j);
				}
			}
		}
	}
	if (checkMemberFlags[13])
	{
		for (i=0; i<MAX_PLAYERS; i++)
		{
			if (changed(oldGame->deckCount[i], newGame->deckCount[i]))
			{
				printf("deckCount[%d] has changed\n", i);
			}
		}
	}
	if (checkMemberFlags[14])
	{
		for (i=0; i<MAX_PLAYERS; i++)
		{
			for (j=0; j<MAX_DECK; j++)
			{
				if (changed(oldGame->discard[i][j], newGame->discard[i][j]))
				{
					printf("discard[%d][%d] has changed\n", i, j);
				}
			}
		}
	}
	if (checkMemberFlags[15])
	{
		for (i=0; i<MAX_PLAYERS; i++)
		{
			if (changed(oldGame->discardCount[i], newGame->discardCount[i]))
			{
				printf("discardCount[%d] has changed\n", i);
			}
		}
	}
	if (checkMemberFlags[16])
	{
		for (i=0; i<MAX_DECK; i++)
	       	{
			if (changed(oldGame->playedCards[i], newGame->playedCards[i]))
			{
				printf("playedCards[%d] has changed\n", i);
			}
		}
	}
	if (checkMemberFlags[17])
	{
		if (changed(oldGame->playedCardCount, newGame->playedCardCount))
		{
			printf("playedCardCount has changed\n");
		}
	}
	return;
}

int changed(int old, int new)
{
	if (old != new)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//  This is based largely on the function fullDeckCount(), provided as part of
//  dominion.c with the class materials.
void countCardTypes(int* cardTypeTotals, struct gameState *state, int player)
{
	int i;
	int j;
	for (i=0; i< treasure_map + 1; i++)	//  For each type of card
	{
		printf("i=%d\n", i);
		cardTypeTotals[i] = 0;
		for (j = 0; j < state->deckCount[player]; j++)	//  For each card in the deck
		{
			printf("j=%d, deck[j]=%d\n", j, state->deck[player][j]);
			if (state->deck[player][j] == i)
			{
				cardTypeTotals[i]++;
			}
		}
	}
	return;
}
