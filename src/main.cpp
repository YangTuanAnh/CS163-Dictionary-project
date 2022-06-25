#include "program.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, "CS163 Dictionary");
    SetTargetFPS(60);

    Program Program;
    while (!WindowShouldClose())
    {
        Program.run();
    }

    CloseWindow();
    return 0;
}