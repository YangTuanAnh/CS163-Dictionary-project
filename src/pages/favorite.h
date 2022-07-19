#pragma once
#include <iostream>
#include "../utility/search.h"
#include <raylib.h>
#include "../utility/screen.h"

class Favorite
{
private:
    std::vector<Word *> word;
    Word *selectedWord = NULL;
    Rectangle rec_result[20];
    Rectangle rec_modes{25, 115, 300, 475};
    Rectangle rec_search{340, 115, 630, 65};
    Rectangle rec_reset{340, 115, 175, 65};
    Rectangle rec_def{340, 125, 835, 450};
    Font fnt = LoadFont("../data/Font.ttf");
    std::vector<std::string> Modes = {"Eng - Eng", "Eng - Vie", "Slang", "Emotional"};
    short modeChosen = 2;
    bool goToHome = false;

public:
    Favorite()
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
    }
    Screen update();
    void draw();
    bool LoadDefinition(Word *word);
};