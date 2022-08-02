#pragma once
#include <iostream>
#include "../utility/search.h"
#include <raylib.h>
#include "../utility/screen.h"

extern Word *selectedWord;
extern Font fnt;
extern int* modeChosen;
class Home
{
private:
    bool SearchEdit = false;
    char SearchInput[101] = "";
    std::vector<Word *> word;
    Rectangle rec_result[20];
    Rectangle rec_dictionary {1030, 115, 155, 65};
    Rectangle rec_random{ 885, 115, 135, 65 };
    Rectangle rec_search{305, 115, 570, 65};
    Rectangle rec_modes[5];
    std::vector<std::string> modes = {"Search Word", "Search Def", "Favorite", "History", "Game"};
    std::vector<std::string> dictionary = {"ENG-ENG", "ENG-VIE", "SLANG", "EMOTIONAL"};
    short menuChosen = 0;
    bool dropDowmBox = false;

public:
    Home();
    Screen update();
    void draw();
    ~Home()
    {
    }
};