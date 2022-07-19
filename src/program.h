#pragma once

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include "utility/screen.h"
#include "pages/home.h"
#include "pages/favorite.h"

const int WIDTH = 1200, HEIGHT = 600;

class Program
{
private:
    Rectangle rec_top{0, 0, 1200, 100};
    Home Home;
    Favorite Favorite;
    Screen currScreen = HOME;

public:
    Program()
    {
        Font fnt = LoadFont("../data/Font.ttf");
        fnt.baseSize /= 1.4;
        GuiSetFont(fnt);
        GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, 0xffffffff);
    }
    void run()
    {
        switch (currScreen)
        {
        case HOME:
            currScreen = Home.update();
            break;
        case FAVORITE:
            currScreen = Favorite.update();
            break;
        default:
            break;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currScreen)
        {
        case HOME:
            Home.draw();
            break;
        case FAVORITE:
            Favorite.draw();
            break;
        default:
            break;
        }
        DrawRectangleRec(rec_top, DARKBLUE);
        DrawText("CS163_GROUP8_DICTIONARY", 390, 60, 28, WHITE);
        EndDrawing();
    }
};