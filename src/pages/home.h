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
    Rectangle rec_result[20];
    Rectangle rec_modes{25, 115, 310, 470};
    Rectangle rec_search{370, 115, 620, 65};
    Font fnt = LoadFont("../data/Font.ttf");
    std::vector<std::string> Modes = {"Eng-Eng", "Eng-Vie", "Slang", "Emotional", "ABC", "CDE"};

public:
    void
    update();
    void draw();
};