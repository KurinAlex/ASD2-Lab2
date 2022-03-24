#pragma once

template <class KeyType, class ValueType>
struct HashNode
{
	KeyType key;
	ValueType value;

	HashNode()
	{
	}

	HashNode(KeyType key, ValueType value)
	{
		this->key = key;
		this->value = value;
	}
};