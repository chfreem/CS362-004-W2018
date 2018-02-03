#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//  The characters I want to generate vary between ascii
	//  32 (the space) and 125 (the right curly brace)
	int randomNum = rand()%126 + 32;
	char c = (char)randomNum;
	return c;
}

char *inputString()
{
	//  With thanks to https://stackoverflow.com/questions/12380758/
	//  for help with malloc
	//  Because I am looking for a specific order of
	//  output, but there is a time limit on the generation of
	//  it, I'm going to restrict my output to the characters
	//  in "reset\0".
	char* targetString = "reset";	//  This automatically
	//	creates an array of 6 elements, with the last element being the
	//	null terminator.  These are the characters we want to
	//	draw from in our random selection.
	char randomChar;
	
	char* randomString = malloc(sizeof(char)*7);
	int i;

	//  For each letter we want to fill in the randomString,
	//  we'll generate a random number in the range [0,5]
	//  and use that as our index to get a character from the
	//  target string.  Then we'll assign it to the string that we'll
	//  return.
	for (i=0; i<6; i++)
	{
		int randomNum = rand()%6;
		randomChar = targetString[randomNum];
		randomString[i] = randomChar;
	}
	randomString[7] = '\0';
	return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
    //  I added this line to testme() so that I don't have a memory leak
    //  from the malloc call in testme()
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
