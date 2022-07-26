#pragma once
#include "home.h"

struct Definitionmenu
{
private:
    Rectangle rec_box{ 50, 120, 1100, 460 };
    Rectangle rec_def{ 50, 210, 1100, 300 };
    std::string fullDef;
public:
    Definitionmenu();
    ~Definitionmenu()
    {
    }
    Screen update();
    void draw();
};
