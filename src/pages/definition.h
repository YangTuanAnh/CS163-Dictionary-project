#pragma once
#include "home.h"

struct Definitionmenu
{
private:
    Rectangle rec_box{ 100, 125, 1000, 455 };
    Rectangle rec_def{ 100, 185, 800, 300 };
    std::string fullDef;
    Vector2* scroll = nullptr;
public:
    Definitionmenu()
    {
    }
    ~Definitionmenu()
    {
    }
    Screen update();
    void draw();
};
