#pragma once

#include <string>
#include "limits.h"

enum Trie_error
{
	success,
	non_exist,
	duplicated_error,
	invalid_character
};

int alphabetic_branch(char x); // Returns the alphabetic order of x

template <class Record, int branch_limit>
class Trie_Node
{
public:
	// data members
	Record data;
	Trie_Node<Record, branch_limit> **branch;
	// Constructors
	Trie_Node(Record data);
	// Destructor
	~Trie_Node();
};

template <class Record, int branch_limit>
class Trie
{
public:
	// Constructor
	Trie(const Record& defaultVal);
	// Destructor
	~Trie();
	// Methods
	Trie_error find(const std::string &target, Record &data);
	Trie_error insert(const std::string &newData, const Record &data);
	std::vector<Record> search(const std::string &key);
private:
	Record defaultValue;
	Trie_Node<Record, branch_limit> *root;
	void getSearchResults(Trie_Node<Record, branch_limit> *cur, std::vector<Record> &results);
};



int alphabetic_branch(char x)
// Returns the branch corresponding to char x
{
	return int(x);
	/*
	// ASCII used
	// Currently for English alphabet
	if (x >= 97 && x <= 122) // Lowercase
		return x - 97;
	else if (x >= 65 && x <= 90) // Uppercase
		return x - 65;
	return -1; // Not a letter
	*/
}
/*******************************************************************************************************/

template <class Record, int branch_limit>
Trie_Node<Record, branch_limit>::Trie_Node(Record data)
{
	this->data = data;
	this->branch = new Trie_Node<Record, branch_limit> *[branch_limit];
	for (int i = 0; i < branch_limit; ++i) {
		branch[i] = nullptr;
	}
}

template <class Record, int branch_limit>
Trie_Node<Record, branch_limit>::~Trie_Node()
{
	for (int i = 0; i < branch_limit; ++i) {
		if (branch[i] != nullptr) {
			delete branch[i];
		}
	}
	delete[] this->branch;
	this->branch = nullptr;
}

/*******************************************************************************************************/
// Trie Defs

template <class Record, int branch_limit>
Trie<Record, branch_limit>::Trie(const Record &defaultVal)
{
	defaultValue = defaultVal;
	root = new Trie_Node<Record, branch_limit>(defaultValue);
}

template <class Record, int branch_limit>
Trie<Record, branch_limit>::~Trie()
{
	delete root;
}

template <class Record, int branch_limit>
Trie_error Trie<Record, branch_limit>::find(const std::string &target, Record &data)
/* Search from the root of Trie, if target is found, result is assigned as a copy of target and return success.
 * Otherwise, return non_exist.
 */
{
	Trie_Node<Record, branch_limit> *cur = root;
	for (auto c : target) {
		int brachId = alphabetic_branch(c);
		if (brachId == -1) {
			return non_exist;
		}
		if (cur->branch[brachId] == nullptr) {
			return non_exist;
		}
		cur = cur->branch[brachId];
	}
	if (cur->data == defaultValue) {
		return non_exist;
	} else {
		data = cur->data;
		return success;
	}
}

template <class Record, int branch_limit>
Trie_error Trie<Record, branch_limit>::insert(const std::string &newData, const Record &data)
/* If new_Data has yet appeared in the Trie, a new Trie_Node with data = new_Data is inserted to Trie and return
success. Otherwise, return duplicated_error */
{
	Trie_Node<Record, branch_limit> *cur = root;
	for (auto c : newData) {
		int brachId = alphabetic_branch(c);
		if (brachId == -1) {
			return invalid_character;
		}
		if (cur->branch[brachId] == nullptr) {
			cur->branch[brachId] = new Trie_Node<Record, branch_limit>(defaultValue);
		}
		cur = cur->branch[brachId];
	}
	if (cur->data == defaultValue) {
		cur->data = data;
		return success;
	} else {
		return duplicated_error;
	}
}

template <class Record, int branch_limit>
std::vector<Record> Trie<Record, branch_limit>::search(const std::string &key) {
	Trie_Node<Record, branch_limit> *cur = root;
	for (auto c : key) {
		int brachId = alphabetic_branch(c);
		if (brachId == -1) {
			return std::vector<Record>();
		}
		if (cur->branch[brachId] == nullptr) {
			return std::vector<Record>();
		}
		cur = cur->branch[brachId];
	}
	std::vector<Record> results;
	Trie<Record, branch_limit>::getSearchResults(cur, results);
	return results;
}

template <class Record, int branch_limit>
void Trie<Record, branch_limit>::getSearchResults(Trie_Node<Record, branch_limit> *cur, std::vector<Record> &results) {
	if (cur == nullptr || results.size() >= SEARCH_RESULTS_LIMIT) {
		return;
	}
	if (cur->data != defaultValue) {
		results.push_back(cur->data);
	}
	for (int i = 0; i < branch_limit; ++i) {
		Trie<Record, branch_limit>::getSearchResults(cur->branch[i], results);
	}
}