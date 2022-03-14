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

std::string generateRandString()
{
	std::string s = "";
	for (int i = 0; i < 10; i++)
	{
		s += rand() % 26 + 'A';
	}
	return s;
}