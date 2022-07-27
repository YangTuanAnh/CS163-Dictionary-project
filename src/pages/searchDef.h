#pragma once
#include <iostream>
#include "home.h"

class SearchDef
{
private:
    bool SearchEdit = false;
    char SearchInput[200] = "";
    std::vector<Word*> word;
    Rectangle rec_result[50];
    Rectangle rec_dictionary{ 1030, 115, 155, 65 };
    Rectangle rec_search{ 305, 115, 710, 65 };
    Rectangle rec_modes[5];
    std::vector<std::string> modes = { "Search Word", "Search Def", "Favorite", "History", "Game" };
    std::vector<std::string> dictionary = { "ENG-ENG", "ENG-VIE", "SLANG", "EMOTIONAL" };
    int* modeChosen = nullptr;
    short menuChosen = 1;
    bool dropDowmBox = false;

public:
    SearchDef();
    Screen update();
    void draw();
    ~SearchDef()
    {
        delete modeChosen;
    }
};