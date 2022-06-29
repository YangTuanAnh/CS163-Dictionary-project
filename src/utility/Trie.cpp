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
template <class Record>
Trie_Node<Record>::Trie_Node()
{
	for (int i = 0; i < MAX_BRANCH; i++)
		branch[i] = nullptr;
}
/*******************************************************************************************************/
// Trie Defs

template <class Record>
Trie<Record>::Trie()
{
	root = nullptr;
}

template <class Record>
Error_Code Trie<Record>::trie_search(Record target, Record &result)
{
	int position = 0;
	Trie_Node<Record> *cur_Node = root;
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
