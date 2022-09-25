# 📘 CS163 Technical Report, APCS1 - Group08

A technical report explaining our design and algorithms when loading a dataset, searching, adding, updating, or deleting a word; evaluating the O notation of every action, and report the running time.

## 👉 Base Structures

In our product, every dictionary is built under the type name of class Dictionary. Class Dictionary consists of the following members:

- Directory of data file
- 3 vectors storing all Definitions, Words and history, respectively. Definition and Word are defined as C++ classes, and will be explained below.
- A trie data structure for storing and searching words. Class Trie will be discussed below.
- A trie data structure for storing and searching definitions.
- Auxiliaries functions.

### Class Word

We first define a dictionary's most basic data, words, by creating a C++ class Words whose members are:

- A std::string to store the spelling of that Word.
- An integer storing the index of the Word in Dictionary::allWords vector.
- A pointer of class Definition pointing to its definition(s).
- UI's auxiliary data.
- A copy constructor.

There is also a class called ResourceWord defined in our project which is used for searching Word-to-Def. This class' data is the same as class Word, there are only minor adding/removing of members and will not be discussed here.

### Class Definition

Next we built a class representing the next significant data of a dictionary, the definitions, as the class Definition. Definition's members includes:

- A std::string storing the definition it represents.
- A pointer of class Word pointing to the Word that has this Definition as one of its definitions. Now we conclude the relations of Words and Definitions, Word-Definitions is a one-to-many relation while the reversal is one-to-one. This is true because realistically, a word may have multiple definitions defined in different contexts.
- Back End's auxiliary data
- A copy constructor

### Trie Structure

- The base unit of our Trie is the Trie\_Node class. Trie\_Node is defined under a template \<Record\>, which is then used to pass class Word/Resource Word, with these members below:
  - A data whose type is detected by Record.
  - An array of pointers to Record(s) called "branch". This member defines the path(s) to any possible Record, and is later used in storing and searching.
- Trie Structure is created based on the classic Trie. with Trie\_Node(s) as nodes of the tree structure and also has the same template \<Record\>. Our Trie has following data members:
  - A char array which stores the path indices of allowed characters.
  - An integer branchLimit limiting the maximum number of branches one node may have.
  - A defaultValue for Record, representing null status.
  - A Trie\_Node pointer _root_, is the root of the tree structure
- Along with various auxiliary functions used for UI/BE/Both. And we only discuss the insert and delete function.
- Inserting
  - To insert a new data to the Trie, we use this function
  ```
  template <class Record>
  Trie_error Trie<Record>::insert (const std::string& newData, cost Record& data)
  ```
  - If new\_Data has yet appeared in the Trie, a new Trie\_Node with data = new\_Data is inserted to Trie and return success. Otherwise, return duplicated\_error.
  - The function loops through the parameter newData, getting the integer value of each character to direct the path. If a character is not allowed, return invalid\_character error. If a path exists, move to the next character of newData, else create a new node at that position.
  - At the end, if the destination node is still defaultValue, assign newData to that node's data. Otherwise, return duplicated\_error.
  - This function uses 1 loop through the string newData, therefore its complexity is linear with the length of newData, which is O(n).
  - Other functions involving traversing the Trie such as find(), search(), trie\_delete()..., just like Inserting, are all linear with the input string parameter's length. Therefore, they all are of O(n) complexity.
