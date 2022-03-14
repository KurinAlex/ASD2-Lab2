#pragma once

#include "HashNode.h"

template<class ValueType>
class HashTableOpenAdressing
{
	typedef long long KeyType;
	typedef HashNode<KeyType, ValueType> HashNodeType;

private:
	const double c_loadFactor = 0.75;

	size_t m_recordsCount;
	size_t m_capacity;
	HashNodeType* m_recordsArray;
	bool* m_isOccupied;

	size_t find_pos(KeyType key)
	{
		int i = hash(key);
		while (m_isOccupied[i] && m_recordsArray[i].key != key)
		{
			i = (i + 1) % m_capacity;
		}
		return i;
	}

public:
	HashTableOpenAdressing()
	{
		m_recordsCount = 0;
		m_capacity = 8;
		m_recordsArray = new HashNodeType[m_capacity];
		m_isOccupied = new bool[m_capacity];
		memset(m_isOccupied, false, m_capacity);
	}

	~HashTableOpenAdressing()
	{
		delete[] m_recordsArray;
		delete[] m_isOccupied;
	}

	size_t hash(KeyType key)
	{
		return key % m_capacity;
	}

	void insert(KeyType key, ValueType value)
	{
		int i = find_pos(key);
		if (m_isOccupied[i])
		{
			m_recordsArray[i].value = value;
			return;
		}

		m_recordsArray[i] = HashNodeType(key, value);
		m_isOccupied[i] = true;

		if (++m_recordsCount / m_capacity > c_loadFactor)
		{
			size_t oldCapacity = m_capacity;
			HashNodeType* tmpRecords = m_recordsArray;
			bool* tmpIsOccupied = m_isOccupied;

			m_recordsCount = 0;
			m_capacity *= 2;
			m_recordsArray = new HashNodeType[m_capacity];
			m_isOccupied = new bool[m_capacity];
			memset(m_isOccupied, false, m_capacity);

			for (int i = 0; i < oldCapacity; i++)
			{
				if (tmpIsOccupied[i])
				{
					insert(tmpRecords[i].key, tmpRecords[i].value);
				}
			}

			delete[] tmpRecords;
			delete[] tmpIsOccupied;
		}
	}

	HashNodeType* find(KeyType key)
	{
		int i = find_pos(key);
		if (m_isOccupied[i])
		{
			return &m_recordsArray[i];
		}
		return nullptr;
	}

	void erase(KeyType key)
	{
		int i = find_pos(key);
		if (!m_isOccupied[i])
		{
			return;
		}

		m_recordsCount--;
		int j = i;
		bool exit = false;
		do
		{
			m_isOccupied[i] = false;
			exit = false;
			while (true)
			{
				j = (j + 1) % m_capacity;
				if (!m_isOccupied[j])
				{
					exit = true;
					break;
				}
				int k = hash(m_recordsArray[j].key);
				if (i <= j ? (i < k && k <= j) : (i < k || k <= j))
				{
					continue;
				}
				m_recordsArray[i] = m_recordsArray[j];
				m_isOccupied[i] = true;
				i = j;
				break;
			}
		} while (!exit);
	}

	size_t size()
	{
		return m_recordsCount;
	}
};