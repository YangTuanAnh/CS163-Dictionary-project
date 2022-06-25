#pragma once
#include <iostream>

class Home
{
private:
    const int WIDTH = 1000, HEIGHT = 600;
    bool SearchEdit = false;
    char SearchInput[101];

public:
    void update()
    {
    }
    void draw()
    {
        if (GuiTextBox({130, 170, 800, 30}, SearchInput, 20, SearchEdit))
            SearchEdit ^= 1;
    }
};