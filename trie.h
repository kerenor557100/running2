﻿#pragma once
#include "TrieNode.h"
#include<vector>
class trie
{
public:
	TrieNode* root;

	bool search(string);  //checks if this word exist in our tree

	void insert(string);  // insert a new word

	bool del(string);  //Deleting a word we chose

	int printAutoSuggestions(string);

	trie(); //default constructor
	~trie();  //destructor

private:
	void deleteSubTree(TrieNode*, bool&);

	bool search(TrieNode*, string, int);     //checks if exist

	bool del(TrieNode*, string, int, bool&, int&); //deletes a word from the tree (if we found the word..)

	void insert(TrieNode*, string, int);  //insert a word 

	void printAutoSuggestions(TrieNode*, vector<string> &, string, int&);
};

