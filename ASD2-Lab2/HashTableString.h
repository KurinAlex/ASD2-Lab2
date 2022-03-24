#pragma once

#include <string>

#include "HashTable.h"

template<class ValueType>
class HashTableString : public HashTable<std::string, ValueType>
{
public:
	HashTableString()
	{
		this->m_loadFactor = 10;
	}

	size_t hash(std::string key) override
	{
		int sum = 0;
		for (char c : key)
		{
			sum += c;
		}
		return sum % this->m_bucketsCount;
	}
};