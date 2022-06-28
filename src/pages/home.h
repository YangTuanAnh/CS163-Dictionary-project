#pragma once
#include <iostream>
#include "../../include/raygui.h"
#include "../utility/search.h"

class Home
{
private:
    const int WIDTH = 1200, HEIGHT = 850;
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word*> word;
    Rectangle rec_result[20];
    Rectangle rec_modes{ 25, 115, 310, 720 };
    Rectangle rec_search{ 370, 115, 620, 65 };
    Font fnt = LoadFont("CS163_github/data/Font.ttf");
public:
    void update();
    void draw();
};