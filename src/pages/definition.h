#pragma once
#include "home.h"

struct Definitionmenu
{
private:
    Rectangle rec_box{ 100, 125, 1000, 455 };
    std::string fullDef;
public:
    Screen update();
    void draw();
};
