#pragma once
#include <iostream>
#include "../utility/search.h"
#include <raylib.h>
#include "../utility/screen.h"

class Home
{
private:
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word *> word;
    Word *selectedWord = NULL;
    Rectangle rec_result[20];
    Rectangle rec_modes{25, 115, 300, 475};
    Rectangle rec_search{340, 115, 630, 65};
    Rectangle rec_reset{985, 115, 165, 65};
    Rectangle rec_def{340, 125, 835, 450};
    Font fnt = LoadFont("CS163_github/data/Font.ttf");
    std::vector<std::string> Modes = {"Eng - Eng", "Eng - Vie", "Slang", "Emotional"};
    short modeChosen = 2;
    bool goToFavorites = false;

public:
    Home();
    Screen update();
    void draw();
    bool LoadDefinition(Word *word);
};