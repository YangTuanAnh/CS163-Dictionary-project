#pragma once
#include <iostream>
#include "../utility/search.h"
#include <raylib.h>
#include "../utility/screen.h"

extern Word *selectedWord;
extern Font fnt;
class Home
{
private:
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word *> word;
    Rectangle rec_result[20];
    Rectangle rec_dictionary{805, 115, 165, 65};
    Rectangle rec_random{985, 115, 165, 65};
    Rectangle rec_search{320, 115, 470, 65};
    Rectangle rec_modes[5];
    std::vector<std::string> modes = {"Search Word", "Search Def", "Favorite", "History", "Game"};
    std::vector<std::string> dictionary = {"ENG-ENG", "ENG-VIE", "SLANG", "EMOTIONAL"};
    int *modeChosen = nullptr;
    short menuChosen = 0;
    bool dropDowmBox = false;

public:
    Home();
    Screen update();
    void draw();
    ~Home()
    {
        delete modeChosen;
    }
};