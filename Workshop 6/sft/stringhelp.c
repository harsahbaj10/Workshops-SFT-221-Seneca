#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "stringhelp.h"
#include "log4c.h"
#include <assert.h>

int nextWhite(const char* str)
{
	int i, result = -1;
	for (i = 0; result < 0 && str[i] != '\0'; i++)
	{
		assert(i <= strlen(str));
		if (isspace(str[i]))
		{
			result = i;
		}
	}
	return (result < 0) ? i : result;
}
int isNumber(const char* str, const int len)
{
	int i, result = 1;

	for (i = 0; i < len && result; i++)
	{
		assert(i <= strlen(str));
		
		result = isdigit(str[i]);
	}
	return result;
}

void indexString(struct StringIndex* result, const char* str)
{
	int i, sp = 0;
	l4cPrintf(&log, L4C_INFO, "Test string: %s", str);
	l4cPrintf(&log, L4C_INFO, "START indexString function");
	reportAll(result);


	strcpy(result->str, str);

	if (str[0] != '\0')
	{
		reportCheckChar(str[0], 0);
		result->lineStarts[0] = 0;
		result->numLines = 1;
		reportAll(result);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		assert(i <= strlen(str));
		reportCheckChar(str[i], i);
		l4cPrintf(&log, L4C_INFO, "Checking '\\0' or 'space'");
		while (str[i] != '\0' && isspace(str[i]))
		{
			l4cPrintf(&log, L4C_INFO, "This char either newline or space");
			if (str[i] == '\n')
			{
				l4cPrintf(&log, L4C_INFO, "NEWLINE FOUND! numLine index increase number by 1");
				
				
				result->lineStarts[result->numLines++] = i + 1;
				reportAll(result);
			}
			i++;
			assert(i <= strlen(str));
			l4cPrintf(&log, L4C_INFO, "Check next character...", i, sp);
			reportCheckChar(str[i], i);
		}

		//The new code
		//I add this logic to prevent if the last character is \n
		//if the last character is \n, it should not increase the 
		//amount of word or number
		assert(i <= strlen(str));
		if (str[i] != '\0')
		{
			l4cPrintf(&log, L4C_INFO, "WORD or NUMBER FOUND, start with [%c]\n", str[i]);
			sp = nextWhite(str + i);
			l4cPrintf(&log, L4C_INFO, "Check remainding: [%s]", str + i);
			l4cPrintf(&log, L4C_INFO, "nextWhite: %d", sp);

			if (isNumber(str + i, sp))
			{
				l4cPrintf(&log, L4C_INFO, "NUMBER FOUND! numNumber index increase number by 1");

				result->numberStarts[result->numNumbers++] = i;
				reportAll(result);
			}
			else
			{
				l4cPrintf(&log, L4C_INFO, "WORD FOUND! numWord index increase number by 1");

				result->wordStarts[result->numWords++] = i;
				reportAll(result);
			}
		}
		else
		{
			l4cPrintf(&log, L4C_INFO, "This char is '\\0'");
			sp = 0;
		}
		l4cPrintf(&log, L4C_INFO, "i += sp-1 -> check point i=%d+%d-1=%d", i, sp, i + sp - 1);
		i += sp - 1;
		assert(i <= strlen(str));
		l4cPrintf(&log, L4C_INFO, "Check next character...", i, sp);
	}
	l4cPrintf(&log, L4C_INFO, "END indexString function...");
}
int getNumberLines(const struct StringIndex* idx)
{
	return idx->numLines;
}
int getNumberWords(const struct StringIndex* idx)
{
	return idx->numWords;
}
int getNumberNumbers(const struct StringIndex* idx)
{
	return idx->numNumbers;
}
void getWord(char word[], const struct StringIndex* idx, int wordNum)
{
	int i, sp, start;
	word[0] = '\0';
	if (wordNum < idx->numWords && wordNum >= 0)
	{
		start = idx->wordStarts[wordNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i < sp; i++)
		{
			word[i] = idx->str[i];
		}
		word[sp] = '\0';
		((struct StringIndex*)idx)->numWords--;
	}
}
void getNumber(char word[], const struct StringIndex* idx, int
	numberNum)
{
	int i, sp, start;
	word[0] = '\0';
	if (numberNum < idx->numNumbers && numberNum >= 0)
	{
		start = idx->numberStarts[numberNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i < sp; i++)
		{
			word[i] = idx->str[start + i];
		}
		word[sp] = '\0';
	}
}
char* getLine(struct StringIndex* idx, int lineNum)
{
	char* result = NULL;
	if (lineNum < idx->numLines && lineNum >= 0)
	{
		result = idx->str + idx->lineStarts[lineNum];
	}
	return result;
}
void printUntil(const char* s, const int start, const char terminator)
{
	int i;
	for (i = start; s[i] != '\0' && s[i] != terminator; i++)
		printf("%c", s[i]);
}
void printUntilSpace(const char* s, const int start)
{
	int i;
	for (i = start; s[i] != '\0' && !isspace(s[i]); i++)
		printf("%c", s[i]);
}

void reportAll(struct StringIndex* result)
{
	int i;
	l4cPrintf(&log, L4C_INFO, "numLines: %d | numWords: %d | numNumbers: %d", result->numLines, result->numWords, result->numNumbers);

	if (result->numLines)
	{
		for (i = 0; i < result->numLines; i++)
		{
			l4cPrintf(&log, L4C_INFO, "lineStarts: %d", result->lineStarts[i]);
		}
		putchar('\n');
	}

	if (result->numWords)
	{
		for (i = 0; i < result->numWords; i++)
		{
			l4cPrintf(&log, L4C_INFO, "wordStarts: %d", result->wordStarts[i]);
		}
		putchar('\n');
	}

	if (result->numNumbers)
	{
		for (i = 0; i < result->numNumbers; i++)
		{
			l4cPrintf(&log, L4C_INFO, "numberStarts: %d", result->numberStarts[i]);
		}
		putchar('\n');
	}
}

void reportCheckChar(char test, int index)
{
	l4cPrintf(&log, L4C_INFO, "Check character = [%c], index = %d", test, index);
}


