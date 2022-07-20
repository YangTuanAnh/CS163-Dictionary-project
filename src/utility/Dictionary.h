#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <chrono>
#include <utility>
#include "Trie.h"
#include "limits.h"

class Word;
class Definition;

class Word
{
public:
    bool isFavorite;
    std::string data;
    std::vector<Definition *> defs;
    Word(const std::string &s);
};

class Definition
{
public:
    std::string data;
    Word *word;
    Definition(const std::string &s);
};

class Dictionary
{
public:
    Dictionary(const std::string &_dir, const std::string &chars);
    ~Dictionary();
    std::vector<Word *> SearchWord(const std::string &word);
    std::vector<Word *> SearchDef(const std::string &key);
    std::vector<std::string> getFullDefinition(const std::string &word);
    void updateFavorite(Word *word);
    void removeFavorite(Word *word);
    std::vector<Word *> getFavoriteList();
    std::vector<int> generateRandQuiz();
    void updateHistory(Word* word, bool addOrDel);

private:
    std::string dir;
    std::vector<Definition *> allDefs;
    std::vector<Word *> allWords, history;
    Trie<Word *> *trie;

    void loadData();
    void loadHistory();
    void loadFavorite();
    std::vector<Word *> getSearchHistory();
    void saveData();
    void saveHistory();
    void saveFavorite();
};

std::vector<std::string> Split(const std::string &s, char delim);
bool IsPrefix(const std::string &p, const std::string &s);
bool checkQuizValidation(int new_option, std::vector<int>& quiz);