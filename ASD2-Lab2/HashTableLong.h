#pragma once

#include "HashTable.h"

template<class ValueType>
class HashTableLong : public HashTable<long long, ValueType>
{
public:
	HashTableLong()
	{
		this->m_loadFactor = 9.65;
	}

	size_t hash(long long key) override
	{
		return key % this->m_bucketsCount;
	}
};