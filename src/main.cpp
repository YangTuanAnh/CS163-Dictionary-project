#include "program.h"
#include "utility/search.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, "CS163_Dictionary");
    SetTargetFPS(60);
    Program Program;
    while (!WindowShouldClose())
        Program.run();
    Deallocate();
    CloseWindow();
    return 0;
}