#pragma once

#include <string>
#include <math.h>
#include "limits.h"

enum Trie_error
{
	success,
	non_exist,
	duplicated_error,
	invalid_character
};

template <class Record>
class Trie_Node
{
public:
	// data members
	Record data;
	Trie_Node<Record>** branch;
	// Constructors
	Trie_Node(int branchLimit, Record data);
	// Destructor
	~Trie_Node();
};

template <class Record>
class Trie
{
public:
	// Constructor
	Trie(const std::string& chars, const Record& defaultVal);
	// Destructor
	~Trie();
	// Methods
	Trie_Node<Record>* getRoot();
	Trie_error find(const std::string& target, Record& data);
	Trie_error insert(const std::string& newData, const Record& data);
	Trie_error trie_delete(const std::string& target);
	std::vector<Record> search(const std::string& key);
	void resetValues();
	void calcValues();
	void clear();
private:
	char alphabeticId[256];
	int branchLimit;
	Record defaultValue;
	Trie_Node<Record>* root;
	void clear(Trie_Node<Record>* root);
	void getSearchResults(Trie_Node<Record>* cur, std::vector<Record>& results);
	void resetValues(Trie_Node<Record>* cur);
	void calcValues(Trie_Node<Record>* cur, double sum);
	void Deallocate(Trie_Node<Record>*& cur);
};

template <class Record>
Trie_Node<Record>::Trie_Node(int branchLimit, Record data)
{
	this->data = data;
	this->branch = new Trie_Node<Record> *[branchLimit];
	for (int i = 0; i < branchLimit; ++i) {
		branch[i] = nullptr;
	}
}

template <class Record>
Trie_Node<Record>::~Trie_Node()
{	
	//std::cerr << "dying" << std::endl;
}

/*******************************************************************************************************/
// Trie Defs

template <class Record>
Trie<Record>::Trie(const std::string& chars, const Record& defaultVal)
{
	branchLimit = chars.size();
	for (int i = 0; i < 256; ++i) {
		alphabeticId[i] = -1;
	}
	for (int i = 0; i < branchLimit; ++i) {
		alphabeticId[(int)chars[i]] = i; 
	}
	defaultValue = defaultVal;
	root = new Trie_Node<Record>(branchLimit, defaultValue);
}

template <class Record>
Trie<Record>::~Trie()
{
	Deallocate(root);
}

template <class Record>
void Trie<Record>::Deallocate(Trie_Node<Record>*& cur) {
	if (cur == nullptr) {
		return;
	}
	for (int i = 0; i < branchLimit; ++i) {
		Deallocate(cur->branch[i]);
	}
	delete cur;
	cur = nullptr;
}

template <class Record>
Trie_error Trie<Record>::find(const std::string& target, Record& data)
/* Search from the root of Trie, if target is found, result is assigned as a copy of target and return success.
 * Otherwise, return non_exist.
 */
{
	Trie_Node<Record>* cur = root;
	for (auto c : target) {
		int brachId = alphabeticId[(int)c];
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
	}
	else {
		data = cur->data;
		return success;
	}
}

template <class Record>
Trie_error Trie<Record>::insert(const std::string& newData, const Record& data)
/* If new_Data has yet appeared in the Trie, a new Trie_Node with data = new_Data is inserted to Trie and return
success. Otherwise, return duplicated_error */
{
	Trie_Node<Record>* cur = root;
	for (auto c : newData) {
		int brachId = alphabeticId[(int)c];
		if (brachId == -1) {
			return invalid_character;
		}
		if (cur->branch[brachId] == nullptr) {
			cur->branch[brachId] = new Trie_Node<Record>(branchLimit, defaultValue);
		}
		cur = cur->branch[brachId];
	}
	if (cur->data == defaultValue) {
		cur->data = data;
		return success;
	}
	else {
		return duplicated_error;
	}
}

template <class Record>
Trie_error Trie<Record>::trie_delete(const std::string& target)
{
	Trie_Node<Record>* cur = root;
	for (auto c : target) {
		int brachId = alphabeticId[(int)c];
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
	}
	else {
		cur->data = defaultValue;
		return success;
	}
}

template <class Record>
std::vector<Record> Trie<Record>::search(const std::string& key) {
	Trie_Node<Record>* cur = root;
	for (auto c : key) {
		int brachId = alphabeticId[(int)c];
		if (brachId == -1) {
			return std::vector<Record>();
		}
		if (cur->branch[brachId] == nullptr) {
			return std::vector<Record>();
		}
		cur = cur->branch[brachId];
	}
	std::vector<Record> results;
	Trie<Record>::getSearchResults(cur, results);
	return results;
}

template <class Record>
void Trie<Record>::clear() {
	clear(root);
	root = new Trie_Node<Record>(branchLimit, defaultValue);
}

template <class Record>
void Trie<Record>::resetValues() {
	resetValues(root);
}

template <class Record>
void Trie<Record>::calcValues() {
	calcValues(root, 0);
}

template <class Record>
void Trie<Record>::getSearchResults(Trie_Node<Record>* cur, std::vector<Record>& results) {
	if (cur == nullptr || results.size() >= SEARCH_RESULTS_LIMIT) {
		return;
	}
	if (cur->data != defaultValue) {
		results.push_back(cur->data);
	}
	for (int i = 0; i < branchLimit; ++i) {
		Trie<Record>::getSearchResults(cur->branch[i], results);
	}
}

template <class Record>
void Trie<Record>::clear(Trie_Node<Record>* root) {
	if (root == nullptr) {
		return;
	}
	if (root->data != defaultValue) {
		delete root->data;
	}
	for (int i = 0; i < branchLimit; ++i) {
		clear(root->branch[i]);
	}
	delete root;
}

template <class Record>
void Trie<Record>::resetValues(Trie_Node<Record>* cur) {
	if (cur == nullptr) {
		return;
	}
	if (cur->data != defaultValue) {
		cur->data->_value = 0;
	}

	for (int i = 0; i < branchLimit; ++i) {
		resetValues(cur->branch[i]);
	}
}

template <class Record>
void Trie<Record>::calcValues(Trie_Node<Record>* cur, double sum) {
	if (cur == nullptr) {
		return;
	}
	if (cur->data != defaultValue) {
		sum += cur->data->_value;
		if (sum >= 1e-2) {
			double val = sum * pow(0.99, (double)cur->data->defs.size());
			for (auto def : cur->data->defs) {
				def->_value += val;
			}
		}
	}

	for (int i = 0; i < branchLimit; ++i) {
		if (cur->branch[i] != nullptr) {
			Trie<Record>::calcValues(cur->branch[i], sum / 2.0);
		}
	}
}

template <class Record>
Trie_Node<Record>* Trie<Record>::getRoot() {
	return root;
}