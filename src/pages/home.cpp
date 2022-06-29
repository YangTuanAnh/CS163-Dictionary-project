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
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < word.size(); i++)
        {
            if (CheckCollisionPointRec(mousePos, rec_result[i]) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                selectedWord = word[i];
        }
    }
}

void Home::draw()
{
    LoadDefinition(selectedWord);

    DrawRectangleRec(rec_modes, WHITE);
    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < Modes.size(); i++)
    {
        Rectangle rec_mode = {rec_modes.x, rec_modes.y + i * (rec_modes.height / Modes.size()), rec_modes.width, rec_modes.height / Modes.size()};
        if (CheckCollisionPointRec(mousePos, rec_mode))
        {
            DrawRectangleRec(rec_mode, LIGHTGRAY);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(rec_mode, GRAY);
                std::cerr << "Load " << Modes[i] << '\n';
            }
        }
        DrawText(Modes[i].c_str(), rec_modes.x + 20, rec_modes.y + rec_modes.height * (i + 0.5) / Modes.size(), 20, BLACK);
    }
    DrawRectangleLinesEx(rec_modes, 3, BLACK);

    DrawRectangleLinesEx(rec_search, 3, BLACK);
    if (GuiTextBox(rec_search, SearchInput, 20, SearchEdit))
        SearchEdit ^= 1;

    if (SearchEdit)
    {
        for (int i = 0; i < word.size(); i++)
        {
            DrawRectangleRec(rec_result[i], DARKBLUE);
            if (CheckCollisionPointRec(mousePos, rec_result[i]))
                DrawRectangleRec(rec_result[i], BLUE);

            DrawTextEx(fnt, word[i]->data.c_str(), {rec_result[i].x + 13, rec_result[i].y + 10}, 25, 2, WHITE);
            for (int j = 0; j < word[i]->defs.size(); j++)
                DrawTextEx(fnt, word[i]->defs[j]->data.c_str(), {rec_result[i].x + 13, rec_result[i].y + 40 * (j + 1)}, 25, 2, WHITE);
        }
    }

    if (GuiButton(rec_search_button, "Search"))
        std::cerr << "Pressed search button\n";

    if (SearchInput[0] == '\0')
        DrawText("Search bar", 375, 135, 30, LIGHTGRAY);
}

void Home::LoadDefinition(Word *word = NULL)
{
    if (!word)
        return;
    DrawRectangleRec(rec_def, WHITE);
    DrawRectangleLinesEx(rec_def, 3, BLACK);

    const int button_width = 45;
    if (GuiButton({rec_def.x + 15, rec_def.y + 15, button_width, button_width}, "->"))
        selectedWord = NULL;
    GuiButton({rec_def.x + rec_def.width - 15 - button_width, rec_def.y + 15, button_width, button_width}, "X");
    GuiButton({rec_def.x + rec_def.width - (15 + button_width) * 2, rec_def.y + 15, button_width, button_width}, "<3");
    GuiButton({rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + 15, button_width, button_width}, "!!");

    DrawTextEx(fnt, word->data.c_str(), {rec_def.x + 15, rec_def.y + 30 + button_width}, 40, 2, BLACK);
    for (int j = 0; j < word->defs.size(); j++)
        DrawTextEx(fnt, word->defs[j]->data.c_str(), {rec_def.x + 15, rec_def.y + 50 + button_width + 40 * (j + 1)}, 25, 2, BLACK);
}