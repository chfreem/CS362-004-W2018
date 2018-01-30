#include "myAssert.h"
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

