#pragma once

#include "HashNode.h"
#include "LinkedList.h"

template<class ValueType>
class HashTable
{
	typedef long long                    KeyType;
	typedef HashNode<KeyType, ValueType> HashNodeType;
	typedef LinkedList<HashNodeType>     LinkedListType;
	typedef Node<HashNodeType>           NodeType;

private:
	const double c_loadFactor = 8.5;

	size_t m_entriesCount;
	size_t m_bucketsCount;
	LinkedListType* m_bucketsArray;

public:
	HashTable()
	{
		m_entriesCount = 0;
		m_bucketsCount = 8;
		m_bucketsArray = new LinkedListType[m_bucketsCount];
	}

	~HashTable()
	{
		delete[] m_bucketsArray;
	}

	size_t hash(KeyType key)
	{
		return key % m_bucketsCount;
	}

	void insert(KeyType key, ValueType value)
	{
		LinkedListType* bucket = &m_bucketsArray[hash(key)];
		NodeType** head = &bucket->head;
		NodeType** current = head;
		while (*current)
		{
			if ((*current)->value.key == key)
			{
				(*current)->value.value = value;
				return;
			}
			current = &((*current)->next);
		}
		bucket->add(HashNodeType(key, value));

		if ((double)++m_entriesCount / m_bucketsCount > c_loadFactor)
		{
			size_t oldCount = m_bucketsCount;
			m_bucketsCount *= 2;
			LinkedListType* tmp = new LinkedListType[m_bucketsCount];
			for (int i = 0; i < oldCount; i++)
			{
				NodeType* current = m_bucketsArray[i].head;
				while (current)
				{
					tmp[hash(current->value.key)].add(current->value);
					current = current->next;
				}
			}
			delete[] m_bucketsArray;
			m_bucketsArray = tmp;
		}
	}

	ValueType* find(KeyType key)
	{
		NodeType* current = m_bucketsArray[hash(key)].head;

		while (current)
		{
			if (current->value.key == key)
			{
				return &current->value.value;
			}
			current = current->next;
		}
		return nullptr;
	}

	void erase(KeyType key)
	{
		NodeType** current = &m_bucketsArray[hash(key)].head;

		while (*current)
		{
			if ((*current)->value.key == key)
			{
				*current = (*current)->next;
				m_entriesCount--;
				return;
			}
			current = &((*current)->next);
		}
	}

	size_t size()
	{
		return m_entriesCount;
	}

	void print()
	{
		for (int i = 0; i < m_bucketsCount; i++)
		{
			std::cout << i << ": ";
			NodeType* current = m_bucketsArray[i].head;
			while (current)
			{
				std::cout << current->value.key << ", ";
				current = current->next;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};