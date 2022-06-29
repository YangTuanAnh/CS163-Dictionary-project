#include "Trie.h"

int alphabetic_branch(char x)
// Returns the branch corresponding to char x
{
	// ASCII used
	// Currently for English alphabet
	if (x >= 97 && x <= 122) // Lowercase
		return x - 97;
	else if (x >= 65 && x <= 90) // Uppercase
		return x - 65;
	return -1; // Not a letter
}
/*******************************************************************************************************/
// Trie_Node Defs
template <class Record, int branch_limit>
Trie_Node<Record, branch_limit>::Trie_Node()
{
	this->max_branch = branch_limit;
	branch = nullptr;
}

template <class Record, int branch_limit>
Trie_Node<Record, branch_limit>::Trie_Node(Record data)
{
	this->data = data;
	this->max_branch = branch_limit;
	this->branch = new Trie_Node<Record, branch_limit> *[max_branch];
}

template <class Record, int branch_limit>
Trie_Node<Record, branch_limit>::~Trie_Node()
{
	delete[] this->branch;
	this->branch = nullptr;
}
/*******************************************************************************************************/
// Trie Defs

template <class Record, int branch_limit>
Trie<Record, branch_limit>::Trie()
{
	root = nullptr;
}

template <class Record, int branch_limit>
Trie<Record, branch_limit>::~Trie()
{
	root = nullptr;
}

template <class Record, int branch_limit>
Error_Code Trie<Record, branch_limit>::trie_search(Record target, Record &result)
/* Search from the root of Trie, if target is found, result is assigned as a copy of target and return success.
 * Otherwise, return non_exist.
 */
{
	int position = 0;
	Trie_Node<Record, branch_limit> *cur_Node = root;
	while (cur_Node && position < target.data.length())
	{
		cur_Node = cur_Node->branch[alphabetic_branch(target.data[position])];
		position++;
	}
	if (cur_Node)
	{
		result = cur_Node->data;
		return success;
	}
	else
		return non_exist;
}

template <class Record, int branch_limit>
Error_Code Trie<Record, branch_limit>::insert(Record new_Data)
/* If new_Data has yet appeared in the Trie, a new Trie_Node with data = new_Data is inserted to Trie and return
success. Otherwise, return duplicated_error */
{
	int position = 0;
	Trie_Node<Record, branch_limit> *cur_Node = root;
	Trie_Node<Record, branch_limit> *next = root;
	while (next && position < new_Data.data.length())
	{
		next = cur_Node->branch[alphabetic_branch(new_Data.data[position])];
		if (next)
		{
			cur_Node = next;
			position++;
		}
	}
	if (next)
	{
		return duplicated_error;
	}
	else
	{
		next = new Trie_Node<Record, branch_limit>(new_Data);
		cur_Node->branch[alphabetic_branch(new_Data.data[position--])] = next;
		return success;
	}
}
