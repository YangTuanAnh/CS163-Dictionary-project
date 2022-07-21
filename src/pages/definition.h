#pragma once
#include "home.h"

struct Definitionmenu
{
private:
    Rectangle rec_def{ 340, 125, 835, 450 };
public:
    Screen update();
    void draw();
};
