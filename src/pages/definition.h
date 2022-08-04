#pragma once
#include "home.h"

struct Definitionmenu
{
private:
    Rectangle rec_box{ 50, 100, 1100, 500 };
    Rectangle rec_def{ 50, 205, 1100, 300 };
    std::string fullDef;
    std::string tmp;
    float propotion;
    int position, pre;
    bool confirmDeleteBox = false;
    bool confirmEditBox = false;
public:
    Definitionmenu();
    ~Definitionmenu()
    {
    }
    Screen update();
    void draw();
    void deleteBox();
};
