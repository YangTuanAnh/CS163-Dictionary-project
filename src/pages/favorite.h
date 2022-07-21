#pragma once
#include "home.h"

class Favorite
{
private:
    std::vector<Word *> word;
    Word *selectedWord = NULL;
    Rectangle rec_result[20];
    Rectangle rec_modes{25, 115, 300, 475};
    Rectangle rec_reset{340, 115, 175, 65};
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
};