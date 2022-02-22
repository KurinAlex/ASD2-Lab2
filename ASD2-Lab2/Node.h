#pragma once

template <class T>
struct Node
{
	T value;
	Node* next;

	Node(T value, Node* next)
	{
		this->value = value;
		this->next = next;
	}
};