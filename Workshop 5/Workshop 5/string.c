/*
*****************************************************************************
                          Workshop - #5
Full Name  : Harsahbaj Singh
Student ID#: 146457221
Email      : hsna27@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int nextWhite(const char* str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (isspace(str[i]))
        {
            return i;
        }
    }
    return i;
}

int isNumber(const char* str, const int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

struct StringIndex indexString(const char* str)
{
    struct StringIndex result = { {0}, {0}, {0}, 0, 0, 0 };
    int i, sp, start;
    strcpy(result.str, str);
    if (str[0] != '\0')
    {
        result.lineStarts[0] = 0;
        result.numLines = 1;
    }
    for (i = 0; str[i] != '\0'; i++)
    {
        while (str[i] != '\0' && isspace(str[i]))
        {
            if (str[i] == '\n')
            {
                result.lineStarts[result.numLines] = i + 1;
                result.numLines++;
            }
            i++;
        }

        start = i;
        sp = nextWhite(str + start);
        if (isNumber(str + start, sp))
        {
            result.numberStarts[result.numNumbers++] = start;

        }
        else
        {
            result.wordStarts[result.numWords++] = start;
            i = start + sp - 1;
        }
    }
    return result;
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
        sp = nextWhite(idx->str + start) - start;
        for (i = 0; i < sp; i++)
        {
            word[i] = idx->str[start + i];
        }
        word[sp] = '\0';
    }
}

void getNumber(char word[], const struct StringIndex* idx, int numberNum)
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

char* getLine(const struct StringIndex* idx, int lineNum)
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

