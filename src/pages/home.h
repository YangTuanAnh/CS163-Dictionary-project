#pragma once
#include <iostream>
#include "../utility/search.h"

class Home
{
private:
    const int WIDTH = 1000, HEIGHT = 600;
    bool SearchEdit = false;
    char SearchInput[101] = "";

public:
    void update()
    {
        if (SearchInput[0] != '\0')
        {
            for (auto word : SearchWord(SearchInput))
                std::cerr << word->data << ' ';
            std::cerr << std::endl;
        }
    }
    void draw()
    {
        if (GuiTextBox({130, 170, 800, 30}, SearchInput, 20, SearchEdit))
            SearchEdit ^= 1;
    }
};