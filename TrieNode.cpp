#include "TrieNode.h"
TrieNode::TrieNode()
{
	numOfSons = 0;

	isEndOfWorld = true;

	parent = NULL;

	for (int i = 0; i < size; i++) //Fill the array with null values
	{
		sons[i] = NULL;
	}
}