#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringhelp.h"
#include "log4c.h"

int main(void)
{
	char errMsg[L4C_ERROR_MSG_MAX + 1] = { "ERROR: open log file" };
	log = l4cOpen("log.txt", 0);

	char testStr[] = { "This is a\n string with embedded newline characters and \n12345 numbers inside it as well 7890" };

	//The old code
	//struct StringIndex index = indexString(testStr);

	//The new code
	//passing by address can trace the variables of the structure directly.
	struct StringIndex index = { {0} };

	if (l4cCheck(&log, errMsg)) printf("%s\n", errMsg);
	else
	{
		indexString(&index, testStr);
		l4cClose(&log);
	}

	int i;
	printf("LINES\n");
	for (i = 0; i < index.numLines; i++)
	{
		printUntil(index.str, index.lineStarts[i], '\n');
		printf("\n");
	}
	printf("\nWORDS\n");
	for (i = 0; i < index.numWords; i++)
	{
		printUntilSpace(index.str, index.wordStarts[i]);
		printf("\n");
	}
	printf("\nNUMBERS\n");
	for (i = 0; i < index.numNumbers; i++)
	{
		printUntilSpace(index.str, index.numberStarts[i]);
		printf("\n");
	}
	 l4cClose("log.txt", 0);
	return 0;
}