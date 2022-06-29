#pragma once
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "pages/home.h"

const int WIDTH = 1200, HEIGHT = 600;
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
    Rectangle rec_top{0, 0, 1200, 100};

public:
    void run()
    {
        switch (Screen)
        {
        case HOME:
            Home.update();
            break;
        default:
            break;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (Screen)
        {
        case HOME:
            Home.draw();
            break;
        default:
            break;
        }
        DrawRectangleRec(rec_top, DARKBLUE);
        DrawText("CS163_GROUP8_DICTIONARY", 390, 60, 28, WHITE);
        EndDrawing();
    }
};