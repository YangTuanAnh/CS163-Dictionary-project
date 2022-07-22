#pragma once
#include <iostream>
#include "../utility/search.h"
#include <raylib.h>
#include "../utility/screen.h"

extern Word* selectedWord;
extern Font fnt;
class Home
{
private:
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word *> word;
    Rectangle rec_result[20];
    Rectangle rec_dictionary {985, 115, 165, 65};
    Rectangle rec_search {340, 115, 630, 65};
    Rectangle rec_favor { 20, 150, 200, 200 };
    Rectangle rec_modes[4];
    std::vector<std::string> modes = { "Search Word", "Search Def", "Favorite", "Game" };
    std::vector<std::string> dictionary = {"ENG-ENG", "ENG-VIE", "SLANG", "EMOTIONAL"};
    int* modeChosen = nullptr;
    short menuChosen = 0;
    bool goToFavorites = false, dropDowmBox = false;
public:
    Home();
    Screen update();
    void draw();
    ~Home()
    {
        delete modeChosen;
    }
};