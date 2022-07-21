#pragma once
#include "home.h"

class Favorite
{
private:
    std::vector<Word *> word;
    Rectangle rec_result[20];
    Rectangle rec_modes[4];
    Rectangle rec_reset{340, 115, 175, 65};
    std::vector<std::string> Modes = { "English - English", "English - Vietnamese", "Slang", "Emotional" };
    short modeChosen = 2;
    bool goToHome = false;

public:
    Favorite()
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
        for (int i = 0;i < 4;i++)
            rec_modes[i] = { 30, (float)200 + 85 * i, 290, 85 };
    }
    Screen update();
    void draw();
};