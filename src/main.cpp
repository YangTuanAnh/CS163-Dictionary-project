#include "program.h"
#include "search.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, "CS163 Dictionary");
    SetTargetFPS(60);
    LoadData("../data/slang.txt");
    Program Program;
    while (!WindowShouldClose())
    {
        Program.run();
    }
    Deallocate();
    CloseWindow();
    return 0;
}