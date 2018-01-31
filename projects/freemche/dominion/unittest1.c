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
#include "testingHelpers.h"
#include "rngs.h"

int main()
{
	int i, a;		//  loop counters
	int seed = 20;	//  for random function
	int maxNumPlayers = 2;	//  we'll test for up to this number of players
	int player;	//  loop counter
	int tooBigDeckSize = MAX_DECK + 6;
//	int tooBigDeckSize = 10;
	int negativeDeckSize = -1;
	int numCardsInDeck;
	int result;	//  for storing the result of initializeGame()

	//  I'm using the same cards as in playdom.c
	int k[10] = {adventurer, gardens, embargo, village, minion, mine,
			cutpurse, sea_hag, tribute, smithy};
	struct gameState currentState;
	struct gameState storedState;	//  For comparison to see if changes
					//  were made
	//  The following array tells the checkStateDifferences()
	//  function which components of the game state should be
	//  checked.  In this case, we don't want to check the
	//  deck (we know it has changed from the shuffling, and
	//  we'll check it more specifically below).
	int checkFlags[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1};
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

	for (a=0; a < 2; a++)	//  Do this twice--once with different cards
				//  and once with identical cards
	{
		for (player = 0; player < maxNumPlayers; player++)
		{
			for  (numCardsInDeck = negativeDeckSize;
				numCardsInDeck < tooBigDeckSize;
				numCardsInDeck++)
			{
				if ((numCardsInDeck < 5) || (numCardsInDeck > 498))
				{	//  We don't want so many printouts--only the interesting ones
					printf("Test player %d with %d cards:  \n", player, numCardsInDeck);
				}

				//  Clear out the previous game state and stored state
				memset(&currentState, '\0', sizeof(struct gameState));
				memset(&storedState, '\0', sizeof(struct gameState));
				result = initializeGame(maxNumPlayers, k, seed, &currentState); 
				if (result < 0)
				{
					printf("Game initialization not successful.\n");
					break;
				}

				//  Now we want to change the game state for
				//  our testing conditions
				currentState.deckCount[player] = numCardsInDeck;
				for (i=0; i < MAX_DECK; i++)
				{
					if (a == 0)
					{
						currentState.deck[player][i] = identicalCards[i];
					}
					else
					{
						currentState.deck[player][i] = differentCards[i];
					}

				}
				copyGame(&currentState, &storedState);
				//  Now we're ready to check the shuffle() function
				result = shuffle(player, &currentState);
				if (result >= 0)
				{
					//  Shuffling was successful
//					for (i=0; i<numCardsInDeck; i++)
//					{
//						printf("%d ", currentState.deck[player][i]);
//					}
//					printf("\n");
//					for (i=0; i<numCardsInDeck; i++)
//					{
//						printf("%d ", storedState.deck[player][i]);
//					}
//					printf("\n");
					//  First, we'll check if any components of the game
					//  state were modified, other than the shuffled
					//  deck.  If so, there will be a report printed to
					//  the screen telling us more info.
					checkStateDifferences(&currentState, &storedState,
							checkFlags);

					//  Next, we want to count how many of each type
					//  of card were in the deck before the shuffle,
					//  and how many are in the deck after the shuffle.
					int storedCardTypeTotals[treasure_map+1];
					memset(&storedCardTypeTotals, '\0', sizeof(int));
					int currentCardTypeTotals[treasure_map+1];
					memset(&currentCardTypeTotals, '\0', sizeof(int));
					countCardTypes(storedCardTypeTotals, &storedState, player);
					countCardTypes(currentCardTypeTotals, &currentState, player);
					int b;
					for (b=0; b<treasure_map+1; b++)
					{
	//					printf("%d ", storedCardTypeTotals[b]);
						if (storedCardTypeTotals[b] != currentCardTypeTotals[b])
						{
							printf("ALERT: after shuffling,");
							printf("card type %d's total ", b);
							printf("has changed.\n");
						}
					}
				}
				else
				{
					printf("shuffling wasn't successful.\n");
				}

			}
		}
	}
	return 0;
}

