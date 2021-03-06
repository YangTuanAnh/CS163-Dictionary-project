#pragma once
#include "home.h"

class History
{
private:
    std::vector<Word *> word;
    Rectangle rec_result[20];
    Rectangle rec_dictionary{985, 115, 165, 65};
    Rectangle rec_search{340, 115, 630, 65};
    Rectangle rec_modes[5];
    std::vector<std::string> modes = {"Search Word", "Search Def", "Favorite", "History", "Game"};
    std::vector<std::string> dictionary = {"ENG-ENG", "ENG-VIE", "SLANG", "EMOTIONAL"};
    int *modeChosen = nullptr;
    short menuChosen = 3;
    bool dropDowmBox = false;

public:
    History()
    {
        modeChosen = new int(0);
        for (int i = 0; i < 20; i++)
            rec_result[i] = {320, (float)200 + 125 * i, 830, 120};
        for (int i = 0; i < 5; i++)
            rec_modes[i] = {30, (float)170 + 90 * i, 245, 60};
        rec_modes[menuChosen] = {20, (float)160 + 90 * menuChosen, 265, 80};
    }
    Screen update();
    void draw();
};