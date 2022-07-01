#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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

extern std::vector<Word*> allWords;
extern std::vector<Definition*> allDefs;

// For UI
std::vector<Word*> get_Search_History();

std::vector<std::string> Split(const std::string& s, char delim);
bool IsPrefix(const std::string& p, const std::string& s);
void LoadHistory();
void updateHistory(Word* word);
void LoadData(const std::string& filePath);
std::vector<Word*> SearchWord(const std::string& word);
std::vector<Word*> SearchDef(const std::string& key);
void Deallocate();

#endif