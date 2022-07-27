#pragma once
#include <raylib.h>
#include "../include/raygui.h"
#include "utility/screen.h"
#include "pages/home.h"
#include "pages/favorite.h"
#include "pages/definition.h"
#include "pages/history.h"
#include "pages/searchDef.h"

const int WIDTH = 1200, HEIGHT = 600;
Font fnt;
class Program
{
private:
    Rectangle rec_top{0, 0, 1200, 100};
    Home Home;
    Favorite Favorite;
    Definitionmenu Definitionmenu;
    History History;
    SearchDef SearchDef;
    Screen currScreen = HOME;

public:
    Program()
    {
        fnt = LoadFont("../data/Font.ttf");
        Font font = fnt;
        font.baseSize /= 1.4;
        GuiSetFont(font);
        GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, 0xffffffff);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    }
    void run()
    {
        switch (currScreen)
        {
        case HOME:
            currScreen = Home.update();
            break;
        case SEARCH_DEF:
            currScreen = SearchDef.update();
            break;
        case FAVORITE:
            currScreen = Favorite.update();
            break;
        case DEFINITION:
            currScreen = Definitionmenu.update();
            break;
        case HISTORY:
            currScreen = History.update();
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
        case SEARCH_DEF:
            SearchDef.draw();
            break;
        case FAVORITE:
            Favorite.draw();
            break;
        case DEFINITION:
            Definitionmenu.draw();
            break;
        case HISTORY:
            History.draw();
            break;
        default:
            break;
        }
        DrawRectangleRec(rec_top, DARKBLUE);
        DrawText("CS163_GROUP8_DICTIONARY", 390, 60, 28, WHITE);
        EndDrawing();
    }
};