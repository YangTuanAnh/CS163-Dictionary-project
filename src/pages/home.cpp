#include "home.h"

void Home::update()
{
    if (SearchInput[0] != '\0')
    {
        word = SearchWord(SearchInput);
    }
    if (GetMouseWheelMove() == -1 && rec_result[word.size() - 1].y > 450)
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
    if (SearchInput[0] != '\0')
    {
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < word.size(); i++)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mousePos.y > 180 && CheckCollisionPointRec(mousePos, rec_result[i]))
                selectedWord = word[i];
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

void Home::draw()
{
    DrawRectangleRec(rec_modes, WHITE);
    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < Modes.size(); i++)
    {
        Rectangle rec_mode = {rec_modes.x, rec_modes.y + i * (rec_modes.height / Modes.size()), rec_modes.width, rec_modes.height / Modes.size()};
        if (CheckCollisionPointRec(mousePos, rec_mode))
        {
            DrawRectangleRec(rec_mode, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRec(rec_mode, GRAY);
                std::cerr << "Load " << Modes[i] << '\n';
            }
        }
        DrawText(Modes[i].c_str(), rec_modes.x + 20, rec_modes.y + rec_modes.height * (i + 0.5) / Modes.size(), 20, BLACK);
    }

    DrawRectangleLinesEx(rec_modes, 3, BLACK);
    if (LoadDefinition(selectedWord))
        return;
    if (SearchInput[0] != '\0')
    {
        for (int i = 0; i < word.size(); i++)
        {
            DrawRectangleRec(rec_result[i], DARKBLUE);
            if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180)
                DrawRectangleRec(rec_result[i], BLUE);

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
            rec_result[i] = { 350, (float)200 + 120 * i,800, 115 };
        SearchEdit ^= 1;
    }

    if (SearchInput[0] == '\0')
        DrawText("Search bar", 375, 135, 30, LIGHTGRAY);

    if (GuiButton(rec_reset, "RESET DB"))
    {
        std::cerr << "Resetted database\n";
    }
}

bool Home::LoadDefinition(Word *word = NULL)
{
    if (!word)
    {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
        return false;
    }
    if (GuiWindowBox(rec_def, "Definition"))
        selectedWord = NULL;
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    //  DrawRectangleRec(rec_def, WHITE);
    //  DrawRectangleLinesEx(rec_def, 3, BLACK);

    const int button_width = 100;
    // if (GuiButton({rec_def.x + 15, rec_def.y + 15, button_width, button_width}, GuiIconText()))
    // selectedWord = NULL;
    GuiButton({rec_def.x + rec_def.width - 15 - button_width, rec_def.y + rec_def.height - 60, button_width, 45}, "Delete");
    GuiButton({rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2, 45}, "Add Favorite");
    GuiButton({rec_def.x + rec_def.width - (15 + button_width) * 4, rec_def.y + rec_def.height - 60, button_width, 45}, "Edit");

    DrawTextEx(fnt, word->data.c_str(), {rec_def.x + 15, rec_def.y + 30 + button_width}, 40, 2, BLACK);
    for (int j = 0; j < word->defs.size(); j++)
        DrawTextEx(fnt, word->defs[j]->data.c_str(), {rec_def.x + 15, rec_def.y + 50 + button_width + 40 * (j + 1)}, 25, 2, BLACK);
    return true;
}