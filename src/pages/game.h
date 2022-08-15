#pragma once
#include "home.h"

class Game
{
private:
    std::vector<Word *> quiz;
    Rectangle rec_modes[5];
    std::vector<std::string> modes = {"Search Word", "Search Def", "Favorite", "History", "Game"};
    std::vector<std::string> dictionary = {"ENG-ENG", "ENG-VIE", "SLANG", "EMOTIONAL"};
    bool isWordGame = true;
    Rectangle rec_gamemode{880, 115, 135, 65};
    Rectangle rec_next{1030, 115, 135, 65};
    short menuChosen = 4;
    bool dropDowmBox = false;
    bool correctAns = false;
    bool pressed = false;
    std::string ans = "";
    Color button_color[4][2] = {{RED, MAROON},
                                {YELLOW, GOLD},
                                {BLUE, DARKBLUE},
                                {LIME, GREEN}};
    std::string options[4] = {"A", "B", "C", "D"};

public:
    Game()
    {
        quiz = data[*modeChosen].generateRandQuiz();
        for (int i = 0; i < 5; i++)
            rec_modes[i] = {30, (float)125 + 90 * i, 245, 60};
        rec_modes[menuChosen] = {20, (float)115 + 90 * menuChosen, 265, 80};
    }
    Screen update();
    void draw();
};