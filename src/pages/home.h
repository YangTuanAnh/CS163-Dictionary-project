#pragma once
#include <iostream>
#include "../utility/search.h"
#include <raylib.h>
#include "../utility/screen.h"
extern Font fnt;
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
    
    std::vector<std::string> Modes = {"Eng - Eng", "Eng - Vie", "Slang", "Emotional"};
    short modeChosen = 2;
    bool goToFavorites = false;

public:
    Home();
    Screen update();
    void draw();
    
};