#pragma once

#include "search.h"

const int MAX_BRANCH = 28;

enum Error_Code
{
	success,
	non_exist
};

template <class Record>
class Trie_Node;
template <class Record>
class Trie;

int alphabetic_branch(char x); // Returns the alphabetic order of x

template <class Record>
class Trie_Node
{
public:
	// data members
	Record *data;
	Trie_Node<Record> *branch[MAX_BRANCH];
	// Constructors
	Trie_Node();
};

template <class Record>
class Trie
{
public:
	// Constructor
	Trie();
	// Methods
	Error_Code trie_search(Record target, Record &result);

private:
	Trie_Node<Record> *root;
};