#pragma once
#include <iostream>
#include "../../include/raygui.h"
#include "../utility/search.h"

class Home
{
private:
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word *> word;
    Word *selectedWord = NULL;
    Rectangle rec_result[20];
    Rectangle rec_modes{25, 115, 310, 475};
    Rectangle rec_search{350, 115, 620, 65};
    Rectangle rec_search_button{1000, 115, 175, 65};
    Rectangle rec_def{350, 200, 825, 390};
    Font fnt = LoadFont("../data/Font.ttf");
    std::vector<std::string> Modes = {"Eng-Eng", "Eng-Vie", "Slang", "Emotional", "ABC", "CDE"};

public:
    Home()
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {350, (float)200 + 120 * i, 825, 115};
    }
    void update();
    void draw();
    void LoadDefinition(Word *word);
};