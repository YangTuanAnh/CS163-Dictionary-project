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
    for (int i = 0; i < word.size(); i++)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]) && !selectedWord)
        {
            selectedWord = word[i];

            slang.getFullDefinition(selectedWord->data);

            for (int i = 0; i < 20; i++)
                rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
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
                modeChosen = i;
                std::cerr << "Load " << Modes[i] << '\n';
            }
        }
        if (modeChosen == i)
            DrawRectangleRec(rec_mode, GRAY);
        DrawTextEx(fnt, Modes[i].c_str(), {rec_modes.x + 70, float(rec_modes.y + rec_modes.height * (i + 0.35) / Modes.size())}, 35, 2, BLACK);
    }
    DrawRectangleLinesEx(rec_modes, 3, BLACK);

    if (definitionPage(selectedWord))
        return;

    for (int i = 0; i < word.size(); i++)
    {
        DrawRectangleRec(rec_result[i], DARKBLUE);
        if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180)
            DrawRectangleRec(rec_result[i], BLUE);

        DrawTextEx(fnt, word[i]->data.c_str(), {rec_result[i].x + 13, rec_result[i].y + 10}, 25, 2, WHITE);
        for (int j = 0; j < std::min(2, int(word[i]->defs.size())); j++)
        {
            std::string s = word[i]->defs[j]->data;
            if (s.length() * 13 > rec_result[i].width - 13)
            {
                for (int k = 0; k < 3; k++)
                    s.insert(s.begin() + rec_result[i].width / 13 + k, '.');
                s.insert(s.begin() + rec_result[i].width / 13 + 3, '\0');
            }
            DrawTextEx(fnt, s.c_str(), {rec_result[i].x + 13, rec_result[i].y + 40 * (j + 1)}, 25, 2, WHITE);
        }
    }
    DrawRectangle(330, 100, 850, 90, RAYWHITE);
    if (GuiButton(rec_reset, "HOME"))
    {
        std::cerr << "Go to Home\n";
        goToHome = true;
    }
}

