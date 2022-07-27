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

const std::string digits = "0123456789";
const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
const std::string space = " ";
const std::string ALLCHAR = digits + lowercase + uppercase + symbols + space;

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

class ResourceWord : public Word
{
public:
    std::vector<int> inDefOf;
    ResourceWord(const std::string &s) : Word(s)
    {
    }
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
    std::vector<Word *> SearchDeftoWord(const std::string &key);
    std::vector<std::string> getFullDefinition(const std::string &word);
    void updateFavorite(Word *word);
    void removeFavorite(Word *word);
    std::vector<Word *> getFavoriteList();
    std::vector<int> generateRandQuiz();
    std::vector<Word *> getSearchHistory();
    std::string getRandomWord();
    void updateHistory(Word *word, bool addOrDel);

    // std::vector<Definition*> allDefs;
    // std::vector<Word*> allWords, history;
    // Trie<ResourceWord*>* resource;
private:
    std::string dir;
    std::vector<Definition *> allDefs;
    std::vector<Word *> allWords, history;
    Trie<Word *> *trie;
    Trie<ResourceWord *> *resource;

    void loadData();
    void loadHistory();
    void loadFavorite();
    void saveData();
    void saveHistory();
    void saveFavorite();
};

std::vector<std::string> Split(const std::string &s, char delim);
bool IsPrefix(const std::string &p, const std::string &s);
bool checkQuizValidation(int new_option, std::vector<int> &quiz);
void quick_sort(std::vector<std::pair<int, int>> &a, int high, int low);