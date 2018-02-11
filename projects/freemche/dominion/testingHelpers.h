#ifndef _MY_ASSERT_H 
#define _MY_ASSERT_H

#include <string.h>
#include "dominion.h"

void myAssert(int conditionA, int conditionB, 
		char* condTitle);

void copyGame(struct gameState *oldGame, struct gameState *newGame);

void checkStateDifferences(struct gameState *oldGame, 
		struct gameState *newGame, 
		int checkMemberFlags[NUM_GAMESTATE_MEMBERS]);

int changed(int old, int new);

void countCardTypes(int* cardTypeTotals, struct gameState *state, int player);

int numSpecificCardsInHand(struct gameState *state, int player, int cardToCount);

int numSpecificCardsInDeck(struct gameState *state, int player, int cardToCount);

int numSpecificCardsInDiscard(struct gameState *state, int player, int cardToCount);
#endif
