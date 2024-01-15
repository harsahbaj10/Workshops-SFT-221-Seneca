#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_FACTORIALS 20
#define NUM_FACTS 20

struct FactorialResults
{
	unsigned long long results[MAX_FACTORIALS];
	int numResults;
};


unsigned long long factorial(const int n)
{
	

	if (n == 0 || n == 1)
	{
		return n;
	}
	else
	{
		return n * factorial(n - 1);
	}
}


unsigned long long reduceFactorial(const int n, const unsigned long long results)
{
	if (n > 20)
	{
		return factorial(n - 1);
	}

	return (n > 0) ? results / n : 1;
}


void computeFactorials(struct FactorialResults* results, int numFactorials)
{
	int i;
	for (i = 0; i < numFactorials; i++)
	{
		results->results[i] = factorial(i + 1);
	}
	results->numResults = numFactorials;
}


int main(void)
{
	struct FactorialResults results = { {0}, 0 };
	int i;
	computeFactorials(&results, NUM_FACTS);

	for (i = 0; i < NUM_FACTS; i++)
	{
		
		printf("%2d %19llu\n", i + 1, results.results[i]);
	}
	return 0;
}