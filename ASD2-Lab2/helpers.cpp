#include <cstdlib>

#include "helpers.h"

long long generateRandLong()
{
	long long num = 0;
	do
	{
		num = rand() % 10;
	} while (num == 0);
	for (int i = 1; i < 10; i++)
	{
		num = num * 10 + rand() % 10;
	}
	return num;
}