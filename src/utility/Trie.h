#pragma once

#include "search.h"

const int MAX_BRANCH_LIMIT = 28;

enum Error_Code
{
	success,
	non_exist,
	duplicated_error
};

template <class Record, int branch_limit>
class Trie_Node;
template <class Record, int branch_limit>
class Trie;

int alphabetic_branch(char x); // Returns the alphabetic order of x

template <class Record, int branch_limit>
class Trie_Node
{
public:
	// data members
	Record data;
	int max_branch;
	Trie_Node<Record, branch_limit> **branch;
	// Constructors
	Trie_Node();
	Trie_Node(Record data);
	// Destructor
	~Trie_Node();
};

template <class Record, int branch_limit>
class Trie
{
public:
	// Constructor
	Trie();
	// Destructor
	~Trie();
	// Methods
	Error_Code trie_search(Record target, Record &result);
	Error_Code insert(Record new_Data);

private:
	Trie_Node<Record, branch_limit> *root;
};