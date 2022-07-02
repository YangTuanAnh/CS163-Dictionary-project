#include "home.h"
#include "favorites.h"

void Home::update()
{
    word = slang.SearchWord(SearchInput);
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
    for (int i = 0; i < word.size(); i++)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]))
        {
            selectedWord = word[i];

            slang.getFullDefinition(selectedWord->data);

            for (int i = 0; i < 20; i++)
                rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
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
                modeChosen = i;
                std::cerr << "Load " << Modes[i] << '\n';
            }
        }
        if (modeChosen == i)
            DrawRectangleRec(rec_mode, GRAY);
        DrawTextEx(fnt, Modes[i].c_str(), {rec_modes.x + 70, float(rec_modes.y + rec_modes.height * (i + 0.35) / Modes.size())}, 35, 2, BLACK);
    }

    DrawRectangleLinesEx(rec_modes, 3, BLACK);
    if (LoadDefinition(selectedWord))
        return;
    for (int i = 0; i < word.size(); i++)
    {
        DrawRectangleRec(rec_result[i], DARKBLUE);
        if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180)
            DrawRectangleRec(rec_result[i], BLUE);

        DrawTextEx(fnt, word[i]->data.c_str(), {rec_result[i].x + 13, rec_result[i].y + 10}, 25, 2, WHITE);
        for (int j = 0; j <= 1; j++)
        {
            std::string s = word[i]->defs[j]->data;
            if (s.length() * 12 > rec_result[i].width - 13)
            {
                for (int k = 1; k <= 3; k++)
                    s.insert(s.begin() + rec_result[i].width / 12 + k, '.');
                s.insert(s.begin() + rec_result[i].width / 12 + 4, '\0');
            }
            DrawTextEx(fnt, s.c_str(), {rec_result[i].x + 13, rec_result[i].y + 40 * (j + 1)}, 25, 2, WHITE);
        }
    }
    DrawRectangle(350, 100, 850, 90, RAYWHITE);
    DrawRectangleLinesEx(rec_search, 3, BLACK);
    if (GuiTextBox(rec_search, SearchInput, 20, SearchEdit))
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {350, (float)200 + 120 * i, 800, 115};
        SearchEdit ^= 1;
    }

    if (SearchInput[0] == '\0')
        DrawText("Search bar", 365, 135, 30, LIGHTGRAY);

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

    const int button_width = 100;

    GuiButton({rec_def.x + rec_def.width - 15 - button_width, rec_def.y + rec_def.height - 60, button_width, 45}, "Delete");
    if (GuiButton({rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45}, "Add Favorite"))
    {
        insertFavorites(selectedWord);
        printFavorites();
    }
    GuiButton({rec_def.x + rec_def.width - (15 + button_width) * 4, rec_def.y + rec_def.height - 60, button_width, 45}, "Edit");

    DrawTextEx(fnt, word->data.c_str(), {rec_def.x + 15, rec_def.y + 40}, 40, 2, BLACK);
    int cnt = 1;
    for (int j = 0; j < word->defs.size(); j++)
    {
        std::string s = word->defs[j]->data;
        int extended = 1;
        if (s.length() * 10 > rec_def.width - 15)
        {
            int len = (rec_def.width - 15) / 10, temp = len;
            while (temp < s.length())
            {
                while (s[temp] != ' ' && temp < s.length())
                    temp--;
                s.insert(s.begin() + temp, '\n');
                temp += len;
                extended++;
            }
        }
        DrawTextEx(fnt, s.c_str(), {rec_def.x + 15, rec_def.y + 60 + 30 * cnt}, 20, 2, BLACK);
        cnt += extended;
    }
    return true;
}