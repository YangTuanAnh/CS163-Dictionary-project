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
    Rectangle rec_modes{ 25, 115, 300, 475 };
    Rectangle rec_search{ 340, 115, 630, 65 };
    Rectangle rec_reset{ 1000, 115, 175, 65 };
    Rectangle rec_def{ 340, 125, 835, 450 };
    Font fnt = LoadFont("../data/Font.ttf");
    std::vector<std::string> Modes = { "Eng - Eng", "Eng - Vie", "Slang", "Emotional" };
    short modeChosen = 2;

public:
    Home() {
        for (int i = 0; i < 20; i++)
            rec_result[i] = { 340, (float)200 + 120 * i, 800, 115 };
    }
    void update();
    void draw();
    bool LoadDefinition(Word* word);
};