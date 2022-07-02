#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include "Trie.h"
#include "limits.h"

class Word;
class Definition;

class Word
{
public:
    std::string data;
    std::vector<Definition*> defs;
    Word(const std::string& s);
};

class Definition
{
public:
    std::string data;
    Word* word;
    Definition(const std::string& s);
};

class Dictionary 
{
public:
    Dictionary(const std::string& _dir, const std::string& chars);
    ~Dictionary();
    std::vector<Word*> SearchWord(const std::string& word);
    std::vector<Word*> SearchDef(const std::string& key);
    std::vector<std::string> getFullDefinition(const std::string& word);

private:
    std::string dir;
    std::vector<Definition*> allDefs;
    std::vector<Word*> history;
    Trie<Word*>* trie;

    void LoadData();
    void LoadHistory();
    void updateHistory(Word* word);
    std::vector<Word*> getSearchHistory();
    void saveData();
    void saveHistory();
};

std::vector<std::string> Split(const std::string& s, char delim);
bool IsPrefix(const std::string& p, const std::string& s);