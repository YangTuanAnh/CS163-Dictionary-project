#include "program.h"
#include "search.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, "CS163_Dictionary");
    SetTargetFPS(60);
    LoadData("CS163_github/data/slang.txt");
    Program Program;
    Font fnt = LoadFont("CS163_github/data/Font.ttf");
    fnt.baseSize /= 1.4;
    GuiSetFont(fnt);
    GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, 0xffffffff);
    while (!WindowShouldClose())
    {
        Program.run();
    }
    Deallocate();
    CloseWindow();
    return 0;
}