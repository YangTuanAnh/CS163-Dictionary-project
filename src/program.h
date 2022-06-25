#pragma once
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "pages/home.h"

const int WIDTH = 1000, HEIGHT = 600;
enum Screen
{
    HOME = 0,
    HISTORY,
    FAVORITE,
    GAME,
    RESET
};
class Program
{
private:
    Screen Screen = HOME;
    Home Home;

public:
    void run()
    {

        switch (Screen)
        {
        case HOME:
            Home.update();
        default:
            break;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (Screen)
        {
        case HOME:
            Home.draw();
        default:
            break;
        }
        EndDrawing();
    }
};