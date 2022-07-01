#pragma once
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "pages/home.h"
#include "pages/favorites.h"

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
    Rectangle rec_top{ 0, 0, 1200, 100 };

public:
    Home Home;
    Favorites Favorites;
    Program()
    {
        Font fnt = LoadFont("CS163_github/data/Font.ttf");
        fnt.baseSize /= 1.4;
        GuiSetFont(fnt);
        GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, 0xffffffff);
        LoadData("CS163_github/data/slang.txt");
    }
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