#pragma once

#include "HashNode.h"
#include "LinkedList.h"

template<class T>
class HashTable
{
	typedef HashNode<long long, T>   HashNodeType;
	typedef LinkedList<HashNodeType> LinkedListType;
	typedef Node<HashNodeType>       NodeType;

private:
	static const size_t c_bucketsCount = 10000;
	size_t m_entriesCount;
	LinkedListType m_bucketsArray[c_bucketsCount];

public:
	HashTable()
	{
		m_entriesCount = 0;
	}

	size_t hash(long long key)
	{
		return key % c_bucketsCount;
	}

	void insert(long long key, T value)
	{
		NodeType** head = &m_bucketsArray[hash(key)].head;
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
		*head = new NodeType(HashNodeType(key, value), *head);
		m_entriesCount++;
	}

	T* find(long long key)
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

	void erase(long long key)
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