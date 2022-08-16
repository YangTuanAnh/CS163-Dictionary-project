#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <utility>
#include <math.h>
#include "Trie.h"
#include "limits.h"

const std::string printable = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

class Word;
class Definition;

class Word
{
public:
    bool isFavorite;
    int index;
    std::string data;
    std::vector<Definition *> defs;
    Word(const std::string &s);
};

class ResourceWord
{
public:
    double _value;
    std::string data;
    std::vector<Definition *> defs;
    ResourceWord(const std::string &s);
};

class Definition
{
public:
    double _value;
    std::string data;
    Word *word;
    Definition(const std::string &s);
};

class Dictionary
{
public:
    Dictionary(const std::string &_dir, const std::string &chars, const std::string &resourceChars);
    ~Dictionary();
    std::vector<Word *> SearchWord(const std::string &word);
    std::vector<Word *> SearchDef(const std::string &key);
    std::vector<std::string> getFullDefinition(const std::string &word);
    
    Word* insertWord(std::string newWord);
    void insertDef(Word* word, std::string newDef);
    void editDef(Definition* def, std::string newData);
    void deleteDef(Definition* def);
    void deleteWord(Word* word);

    void updateFavorite(Word *word);
    void removeFavorite(Word *word);
    std::vector<Word *> getFavoriteList();
    std::vector<Word *> generateRandQuiz();
    std::vector<Word *> getSearchHistory();
    std::string getRandomWord();
    void updateHistory(Word *word, bool addOrDel);
    void resetData();

private:
    std::string dir;
    std::vector<Definition *> allDefs;
    std::vector<Word *> allWords, history;
    Trie<Word *> *trie;
    Trie<ResourceWord *> *resource;

    void updateDefsLinks(Definition *def, int type);

    void loadData(std::string dataFile);
    void loadHistory();
    void loadFavorite();
    void saveData();
    void saveHistory();
    void saveFavorite();
};

std::string Normalize(const std::string &s);
std::vector<std::string> Split(const std::string &s, char delim);
bool IsPrefix(const std::string &p, const std::string &s);
bool checkQuizValidation(int new_option, std::vector<int> &quiz);
int editDistance(const std::string &s, const std::string &t);
