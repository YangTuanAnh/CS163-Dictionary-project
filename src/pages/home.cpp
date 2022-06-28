#include "home.h"

void Home::update() {
    if (SearchInput[0] != '\0')
    {
        word = SearchWord(SearchInput);
    }
    if (GetMouseWheelMove() == -1 && rec_result[word.size() - 1].y > 660)
    {
        for (int i = 0; i < word.size(); i++)
        {
            rec_result[i].y -= 20;
        }
    }
    else if (GetMouseWheelMove() == 1 && rec_result[0].y < 200)
    {
        for (int i = 0; i < word.size(); i++)
        {
            rec_result[i].y += 20;
        }
    }
    if (SearchEdit)
    {
        if (GetKeyPressed())
        {
            for (int i = 0; i < 20; i++)
                rec_result[i] = { 350, (float)200 + 120 * i,800, 115 };
        }
    }
}

void Home::draw() {
    DrawRectangleRec(rec_modes, WHITE);
    DrawRectangleLinesEx(rec_modes, 3, BLACK);
    if (SearchInput[0] != '\0')
    {
        for (int i = 0; i < word.size(); i++)
        {
            DrawRectangleRec(rec_result[i], DARKBLUE);
            DrawTextEx(fnt, word[i]->data.c_str(), { rec_result[i].x + 13, rec_result[i].y + 10 }, 25, 2, WHITE);
            for (int j = 0; j < word[i]->defs.size(); j++)
                DrawTextEx(fnt, word[i]->defs[j]->data.c_str(), { rec_result[i].x + 13, rec_result[i].y + 40 * (j + 1) }, 25, 2, WHITE);
        }
    }
    DrawRectangle(350, 100, 850, 90, RAYWHITE);
    DrawRectangleLinesEx(rec_search, 3, BLACK);
    if (GuiTextBox(rec_search, SearchInput, 20, SearchEdit))
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = { 350, (float)200 + 120 * i,800, 115 };
        SearchEdit ^= 1;
    }
    if (SearchInput[0] == '\0') DrawText("Search bar", 385, 135, 30, LIGHTGRAY);
}