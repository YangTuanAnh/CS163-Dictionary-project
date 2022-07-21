#define _CRT_SECURE_NO_WARNINGS
#define RAYGUI_IMPLEMENTATION
#include "../../include/raygui.h"
#include "home.h"
#include "definition.h"


Home::Home()
{
    char** icon = GuiLoadIcons("icons.rgi", true);
    for (int i = 0; i < 20; i++)
        rec_result[i] = { 350, (float)200 + 120 * i, 800, 115 };
    for (int i = 0;i < 4;i++)
        rec_modes[i] = { 30, (float)200 + 85 * i, 290, 85 };
}

Screen Home::update()
{
    word = slang.SearchWord(SearchInput);
    if (GetMouseWheelMove() == -1 && rec_result[word.size() - 1].y > 475)
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < word.size(); i++)
        {
            if (SearchInput[0] == '\0' && CheckCollisionPointRec(GetMousePosition(), {rec_result[i].x + 715, rec_result[i].y + 5, 32, 32}))
            {
                slang.updateHistory(word[i], false);
                break;;
            }
            else if (CheckCollisionPointRec(GetMousePosition(), { rec_result[i].x + 760, rec_result[i].y + 5, 32, 32 }))
            {
                strncpy(SearchInput, word[i]->data.c_str(), sizeof(word[i]->data));
                break;
            }
            else if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]) && !selectedWord)
            {
                selectedWord = word[i];
                slang.getFullDefinition(selectedWord->data);

                for (int i = 0; i < 20; i++)
                    rec_result[i] = { 350, (float)200 + 120 * i, 800, 115 };
                break;
            }
        }

        for (int i = 0;i < 4;i++)
            if (CheckCollisionPointRec(GetMousePosition(), rec_modes[i]))
            {
                modeChosen = i;
                break;
            }
    }
    
    if (SearchEdit)
    {
        if (GetKeyPressed())
        {
            for (int i = 0; i < 20; i++)
                rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
        }
    }

    if (goToFavorites)
    {
        goToFavorites ^= 1;
        return FAVORITE;
    }
    return HOME;
}

void Home::draw()
{
    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        DrawRectangleRec(rec_modes[i], WHITE);
        if (CheckCollisionPointRec(mousePos, rec_modes[i]))
            DrawRectangleRec(rec_modes[i], LIGHTGRAY);

        if (modeChosen == i)
            DrawRectangleRec(rec_modes[i], LIGHTGRAY);
        DrawTextEx(fnt, Modes[i].c_str(), { rec_modes[i].x + 8, rec_modes[i].y + 27 }, 30, 1.5, BLACK);
        DrawRectangleLinesEx(rec_modes[i], 1.5, BLACK);
    }
    if (definitionPage(selectedWord))
        return;
    for (int i = 0; i < word.size(); i++)
    {
        DrawRectangleRec(rec_result[i], DARKBLUE);
        if (SearchInput[0] == '\0' && CheckCollisionPointRec(mousePos, {rec_result[i].x + 715, rec_result[i].y + 5, 32, 32}))
            GuiDrawIcon(202, rec_result[i].x + 715, rec_result[i].y + 5, 2, RED);
        else if (CheckCollisionPointRec(mousePos, { rec_result[i].x + 760, rec_result[i].y + 5, 32, 32 }))
            GuiDrawIcon(201, rec_result[i].x + 760, rec_result[i].y + 5, 2, GREEN);
        else 
        {
            if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180)
                DrawRectangleRec(rec_result[i], BLUE);
            if (SearchInput[0] == '\0')
                GuiDrawIcon(202, rec_result[i].x + 715, rec_result[i].y + 5, 2, BLACK);
            GuiDrawIcon(201, rec_result[i].x + 760, rec_result[i].y + 5, 2, BLACK);
        }
        if (word[i]->isFavorite) GuiDrawIcon(186, rec_result[i].x + 665, rec_result[i].y + 5, 2, RED);
        else GuiDrawIcon(200, rec_result[i].x + 665, rec_result[i].y + 5, 2, BLACK);
        DrawTextEx(fnt, word[i]->data.c_str(), {rec_result[i].x + 10, rec_result[i].y + 8}, 34, 2, WHITE);
        for (int j = 0; j < std::min(2, int(word[i]->defs.size())); j++)
        {
            std::string s = word[i]->defs[j]->data;
            if (s.length() * 13 > rec_result[i].width - 13)
            {
                for (int k = 0; k < 3; k++)
                    s.insert(s.begin() + rec_result[i].width / 13 + k, '.');
                s.insert(s.begin() + rec_result[i].width / 13 + 3, '\0');
            }
            DrawTextEx(fnt, s.c_str(), {rec_result[i].x + 13, rec_result[i].y + 30 * j + 50}, 25, 2, LIGHTGRAY);
        }
    }
    DrawRectangle(330, 100, 850, 90, RAYWHITE);
    DrawRectangleLinesEx(rec_search, 3, BLACK);
    if (GuiTextBox(rec_search, SearchInput, 20, SearchEdit))
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
        SearchEdit ^= 1;
    }

    if (SearchInput[0] == '\0')
        DrawText("Search bar", 365, 135, 30, LIGHTGRAY);

    if (GuiButton(rec_reset, "FAVORITES"))
    {
        std::cerr << "Go to Favorites\n";
        goToFavorites = true;
    }

}
