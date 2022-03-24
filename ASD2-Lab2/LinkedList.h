#pragma once

#include "Node.h"

template<class T>
struct LinkedList
{
	Node<T>* head;

	LinkedList()
	{
		head = nullptr;
	}

	~LinkedList()
	{
		while (head)
		{
			Node<T>* current = head;
			head = head->next;
			delete current;
		}
	}

	void add(T el)
	{
		head = new Node<T>(el, head);
	}
};