#include <iostream>
#include <ctime>
#include <unordered_map>

#include "HashTable.h"
#include "Data.h"
#include "helpers.h"

using namespace std;

bool testHashTable()
{
	const int iters = 500000;
	const int keysAmount = iters * 1;

	long long* keys = new long long[keysAmount];
	long long* keysToInsert = new long long[iters];
	long long* keysToErase = new long long[iters];
	long long* keysToFind = new long long[iters];
	for (int i = 0; i < keysAmount; i++)
	{
		keys[i] = generateRandLong();
	}
	for (int i = 0; i < iters; i++)
	{
		keysToInsert[i] = keys[generateRandLong() % keysAmount];
		keysToErase[i] = keys[generateRandLong() % keysAmount];
		keysToFind[i] = keys[generateRandLong() % keysAmount];
	}

	HashTable<Data> hashTable;
	clock_t myStart = clock();
	for (int i = 0; i < iters; i++)
	{
		hashTable.insert(keysToInsert[i], Data());
	}
	int myInsertSize = hashTable.size();
	for (int i = 0; i < iters; i++)
	{
		hashTable.erase(keysToErase[i]);
	}
	int myEraseSize = hashTable.size();
	int myFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (hashTable.find(keysToFind[i]) != NULL)
		{
			myFoundAmount++;
		}
	}
	clock_t myEnd = clock();
	float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

	unordered_map<long long, Data> unorderedMap;
	clock_t stlStart = clock();
	for (int i = 0; i < iters; i++)
	{
		unorderedMap.insert({ keysToInsert[i], Data() });
	}
	int stlInsertSize = unorderedMap.size();
	for (int i = 0; i < iters; i++)
	{
		unorderedMap.erase(keysToErase[i]);
	}
	int stlEraseSize = unorderedMap.size();
	int stlFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
		{
			stlFoundAmount++;
		}
	}
	clock_t stlEnd = clock();
	float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
	cout << "My HashTable:" << endl;
	cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
		", found amount: " << myFoundAmount << endl;
	cout << "STL unordered_map:" << endl;
	cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
		<< ", found amount: " << stlFoundAmount << endl << endl;
	delete[] keys;
	delete[] keysToInsert;
	delete[] keysToErase;
	delete[] keysToFind;
	if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
		stlFoundAmount)
	{
		cout << "The lab is completed" << endl;
		return true;
	}
	cerr << ":(" << endl;
	return false;
}

int main()
{
	srand(time(0));

	testHashTable();
}