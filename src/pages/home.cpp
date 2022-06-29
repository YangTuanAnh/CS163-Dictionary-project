#include "home.h"

void Home::update()
{
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
                rec_result[i] = {350, (float)200 + 120 * i, 825, 115};
        }
    }
}

void Home::draw()
{
    DrawRectangleRec(rec_modes, WHITE);

    Vector2 mousePos = GetMousePosition();
    if (rec_modes.x <= mousePos.x && mousePos.x <= rec_modes.x + rec_modes.width &&
        rec_modes.y <= mousePos.y && mousePos.y <= rec_modes.y + rec_modes.height)
    {
        int index = (mousePos.y - rec_modes.y) / (rec_modes.height / Modes.size());
        if (index < Modes.size())
        {
            DrawRectangle(rec_modes.x, rec_modes.y + index * (rec_modes.height / Modes.size()), rec_modes.width, rec_modes.height / Modes.size(), LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                DrawRectangle(rec_modes.x, rec_modes.y + index * (rec_modes.height / Modes.size()), rec_modes.width, rec_modes.height / Modes.size(), GRAY);
                std::cerr << "Load " << Modes[index] << '\n';
            }
        }
    }
    for (int i = 0; i < Modes.size(); i++)
    {
        DrawTextEx(fnt, Modes[i].c_str(), { rec_modes.x + 20, rec_modes.y + rec_modes.height * (i + (float)0.4) / Modes.size() }, 30, 2, BLACK);
    }
    DrawRectangleLinesEx(rec_modes, 3, BLACK);

    if (SearchInput[0] != '\0')
    {
        for (int i = 0; i < word.size(); i++)
        {
            DrawRectangleRec(rec_result[i], DARKBLUE);
            DrawTextEx(fnt, word[i]->data.c_str(), {rec_result[i].x + 13, rec_result[i].y + 10}, 25, 2, WHITE);
            for (int j = 0; j < word[i]->defs.size(); j++)
                DrawTextEx(fnt, word[i]->defs[j]->data.c_str(), {rec_result[i].x + 13, rec_result[i].y + 40 * (j + 1)}, 25, 2, WHITE);
        }
    }
    DrawRectangle(350, 100, 850, 90, RAYWHITE);
    DrawRectangleLinesEx(rec_search, 3, BLACK);
    if (GuiTextBox(rec_search, SearchInput, 20, SearchEdit))
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {350, (float)200 + 120 * i, 825, 115};
        SearchEdit ^= 1;
    }

    if (GuiButton(rec_search_button, "SEARCH"))
        std::cerr << "Pressed search button\n";

    if (SearchInput[0] == '\0')
        DrawText("Search bar", 380, 135, 30, LIGHTGRAY);
}