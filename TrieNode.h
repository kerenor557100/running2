#pragma once
#include <iostream>
using namespace std;
const int size = 58;  // all the letters 

class TrieNode
{
public:
	bool isEndOfWorld;

	TrieNode* sons[size]; //array of letters

	TrieNode* parent;

	int numOfSons;

	TrieNode();
};
