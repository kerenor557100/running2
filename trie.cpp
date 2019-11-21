#include "TrieNode.h"
#include "trie.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
trie::trie()
{
	root = new TrieNode();  // New empty tree
}


trie::~trie()
{
	bool f = false;
	deleteSubTree(root, f); //delete everything!
}




void trie::insert(string word)  //insert a word to our tree
{
	insert(root, word, 0);
}


void trie::insert(TrieNode* roo, string word, int N)
{
	TrieNode* ThePointerToTheNextTav;
	if (N == word.length())  //after the last character 
	{
		return;
	}
	else  if (roo->sons[word[N] - 'A'])  //if alredy exist
	{
		if (N == word.length() - 1)  //isEndOfWorld->true
			roo->sons[word[N] - 'A']->isEndOfWorld = true;

		ThePointerToTheNextTav = roo->sons[word[N] - 'A'];  //insert the next character- his number in the string: num+1
		insert(ThePointerToTheNextTav, word, ++N);
	}
	else
	{

		roo->sons[word[N] - 'A'] = new TrieNode();
		roo->sons[word[N] - 'A']->parent = roo;
		roo->numOfSons++; //sons++

		if (N != word.length() - 1) //there is more characters

			roo->sons[word[N] - 'A']->isEndOfWorld = false;

		ThePointerToTheNextTav = roo->sons[word[N] - 'A'];
		insert(ThePointerToTheNextTav, word, ++N);
	}
}
void trie::deleteSubTree(TrieNode* roo, bool& erase)
{
	bool f = false;
	if (roo->numOfSons == 0)
	{
		if (roo->parent)  // sons of a parent--
		{
			roo->parent->numOfSons -= 1;
			erase = true;
			delete roo;
		}
		return;
	}
	else
	{
		for (int i = 0; i < size; i++) //all the sons
			if (roo->sons[i])  //if there is a son, we need to deletes him 
				deleteSubTree(roo->sons[i], f);
		if (roo->parent) //sons of a parent--
			roo->parent->numOfSons -= 1;
		delete roo;
	}
}

bool trie::del(string word) //deletes a word from our tree.
{
	if (!search(word)) //if not exist
	{
		return false; //can't delete
	}
	bool e = false; //erase
	int deleted = 0; //number of characters that was deleted.
	e = del(root, word, 0, e, deleted);
	TrieNode* putNULL = root;
	int tav = 0;
	int del = deleted;
	while (word.length() - deleted)
	{
		putNULL = putNULL->sons[word[tav++] - 'A'];
		deleted++;
	}
	putNULL->sons[word[tav++] - 'A'] = NULL;
	return e;
}


bool trie::del(TrieNode* roo, string word, int N, bool& e, int& NumberOfdeleted)
{
	TrieNode* ThePointerToTheNextTav;
	if (N == word.length())
	{
		if (roo->numOfSons == 0) //final of word.
		{
			deleteSubTree(roo, e);
		}

		else
			roo->isEndOfWorld = false;
		return true;

	}
	else
	{
		ThePointerToTheNextTav = roo->sons[word[N] - 'A'];
		del(ThePointerToTheNextTav, word, ++N, e, NumberOfdeleted);

		if (e)
		{
			NumberOfdeleted++;
			e = false;
			if (roo->numOfSons == 0)
			{
				deleteSubTree(roo, e);
			}
			else
				return true;;
		}
		return true;
	}
}

bool trie::search(string word)
{
	return search(root, word, 0);
}



bool trie::search(TrieNode* roo, string word, int N)
{
	TrieNode* ThePointerToTheNextTav;
	if (N == word.length())
	{
		return false;
	}

	else if (!roo->sons[word[N] - 'A']) // if one of the characters was not found->return false
	{
		return false;
	}

	else if (N == (word.length() - 1) && roo->sons[word[N] - 'A']->isEndOfWorld)

	{
		return true;
	}

	else
	{
		ThePointerToTheNextTav = roo->sons[word[N] - 'A'];
		return search(ThePointerToTheNextTav, word, ++N);
	}
}


int trie::printAutoSuggestions(string word)
{
	int mone = 0;
	vector<string> allThewords;
	TrieNode* pointer = root;

	for (int i = 0; i < word.length(); i++) //checks if  all the letters exist in the tree
	{
		if (pointer->sons[word[i] - 'A'])
			pointer = pointer->sons[word[i] - 'A'];

		else
			return 0;
	}
	printAutoSuggestions(pointer, allThewords, word, mone);

	if (mone == 0 && pointer->isEndOfWorld)
	{
		cout << word << endl;
		return 1;
	}

	else
	{
		for (int i = 0; i < allThewords.size(); i++) // prints all the words  With the same beginning as we received
			cout << allThewords[i] << endl;
		return mone;
	}
}


void trie::printAutoSuggestions(TrieNode* roo, vector<string> &words, string word, int&count)
{
	if (roo->numOfSons == 0)
	{
		return;
	}

	for (int i = 0; i < size; i++)
	{
		if (roo->sons[i])
		{
			char tav = 'A' + i;

			if (roo->sons[i]->isEndOfWorld)
			{
				words.push_back(word + tav);
				count++;
			}

			else
			{
				TrieNode* t = roo->sons[i];
				printAutoSuggestions(t, words, word + tav, count);
			}
		}
	}
}

