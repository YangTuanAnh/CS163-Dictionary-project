#pragma once
#include <iostream>
#include "../../include/raygui.h"
#include "../utility/search.h"

class Home
{
private:
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word*> word;
    Word* selectedWord = NULL;
    Rectangle rec_result[20];
    Rectangle rec_modes{ 25, 115, 310, 475 };
    Rectangle rec_search{ 350, 115, 620, 65 };
    Rectangle rec_reset{ 1000, 115, 175, 65 };
    Rectangle rec_def{ 350, 125, 825, 450 };
    Font fnt = LoadFont("../data/Font.ttf");
    std::vector<std::string> Modes = { "Eng - Eng", "Eng - Vie", "Slang", "Emotional" };

public:
    void update();
    void draw();
    bool LoadDefinition(Word* word);
};