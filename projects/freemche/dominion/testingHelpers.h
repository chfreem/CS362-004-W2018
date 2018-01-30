#ifndef _MY_ASSERT_H 
#define _MY_ASSERT_H

#include <string.h>
#include "dominion.h"

void myAssert(int conditionA, int conditionB, 
		char* condATitle, char* condBTitle);

void copyGame(struct gameState *oldGame, struct gameState *newGame);

void checkStateDifferences(struct gameState *oldGame, struct gameState *newGame);
#endif
