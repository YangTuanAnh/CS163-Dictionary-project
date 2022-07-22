#include "favorite.h"
#include "../../include/raygui.h"
#include "definition.h"

Screen Favorite::update()
{
    word = slang.getFavoriteList();
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
    if (IsMouseButtonPressed(0))
    {
        for (int i = 0; i < word.size(); i++)
        {
            if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]) && !selectedWord)
            {
                selectedWord = word[i];
                slang.getFullDefinition(selectedWord->data);

                for (int i = 0; i < 20; i++)
                    rec_result[i] = { 350, (float)200 + 120 * i, 800, 115 };
                return DEFINITION;
            }
        }

        for (int i = 0;i < 4;i++)
            if (CheckCollisionPointRec(GetMousePosition(), rec_modes[i]))
            {
                modeChosen = i;
                break;
            }
    }

    if (goToHome)
    {
        goToHome ^= 1;
        for (int i = 0; i < 20; i++)
            rec_result[i] = { 350, (float)200 + 120 * i, 800, 115 };
        return HOME;
    }
    return FAVORITE;
}

void Favorite::draw()
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

    for (int i = 0; i < word.size(); i++)
    {
        DrawRectangleRec(rec_result[i], DARKBLUE);
        if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180)
            DrawRectangleRec(rec_result[i], BLUE);

        DrawTextEx(fnt, word[i]->data.c_str(), { rec_result[i].x + 10, rec_result[i].y + 8 }, 34, 2, WHITE);
        for (int j = 0; j < std::min(2, int(word[i]->defs.size())); j++)
        {
            std::string s = word[i]->defs[j]->data;
            if (s.length() * 13 > rec_result[i].width - 13)
            {
                for (int k = 0; k < 3; k++)
                    s.insert(s.begin() + rec_result[i].width / 13 + k, '.');
                s.insert(s.begin() + rec_result[i].width / 13 + 3, '\0');
            }
            DrawTextEx(fnt, s.c_str(), { rec_result[i].x + 13, rec_result[i].y + 30 * j + 50 }, 25, 2, LIGHTGRAY);
        }
    }
    DrawRectangle(330, 100, 850, 90, RAYWHITE);
    if (GuiButton(rec_reset, "HOME"))
    {
        std::cerr << "Go to Home\n";
        goToHome = true;
    }
}

