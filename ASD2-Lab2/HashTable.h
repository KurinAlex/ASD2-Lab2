#pragma once

#include "HashNode.h"
#include "LinkedList.h"

template<class KeyType, class ValueType>
class HashTable
{
	typedef HashNode<KeyType, ValueType> HashNodeType;
	typedef LinkedList<HashNodeType>     LinkedListType;
	typedef Node<HashNodeType>           NodeType;

protected:
	const double c_loadFactor = 9.65;
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

	virtual size_t hash(KeyType key) = 0;

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
			for (size_t i = 0; i < oldCount; i++)
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

	HashNodeType* find(KeyType key)
	{
		NodeType* current = m_bucketsArray[hash(key)].head;

		while (current)
		{
			if (current->value.key == key)
			{
				return &current->value;
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
};