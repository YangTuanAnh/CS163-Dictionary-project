#define _CRT_SECURE_NO_WARNINGS
#define RAYGUI_IMPLEMENTATION
#include "../../include/raygui.h"
#include "home.h"
Home::Home()
{
    char** icon = GuiLoadIcons("icons.rgi", true);
    for (int i = 0; i < 20; i++)
        rec_result[i] = { 350, (float)200 + 120 * i, 800, 115 };
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
            if (SearchInput[0] == '\0' && CheckCollisionPointRec(GetMousePosition(), { rec_result[i].x + 650, rec_result[i].y + 30, 48, 48 }))
            {
                slang.updateHistory(word[i], false);
            }
            else if (CheckCollisionPointRec(GetMousePosition(), { rec_result[i].x + 720, rec_result[i].y + 30, 48, 48 }))
                strncpy(SearchInput, word[i]->data.c_str(), sizeof(word[i]->data));
            else if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]) && !selectedWord)
            {
                selectedWord = word[i];
                slang.getFullDefinition(selectedWord->data);

                for (int i = 0; i < 20; i++)
                    rec_result[i] = { 350, (float)200 + 120 * i, 800, 115 };
            }
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
        if (SearchInput[0] == '\0' && CheckCollisionPointRec(mousePos, {rec_result[i].x + 650, rec_result[i].y + 30, 48, 48}))
            GuiDrawIcon(202, rec_result[i].x + 650, rec_result[i].y + 30, 3, RED);
        else if (CheckCollisionPointRec(mousePos, { rec_result[i].x + 720, rec_result[i].y + 30, 48, 48 }))
            GuiDrawIcon(201, rec_result[i].x + 720, rec_result[i].y + 30, 3, GREEN);
        else 
        {
            if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180)
                DrawRectangleRec(rec_result[i], BLUE);
            if (SearchInput[0] == '\0')
                GuiDrawIcon(202, rec_result[i].x + 650, rec_result[i].y + 30, 3, BLACK);
            GuiDrawIcon(201, rec_result[i].x + 720, rec_result[i].y + 30, 3, BLACK);
        }
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

bool Home::LoadDefinition(Word *word = NULL)
{
    if (!selectedWord)
    {
        return false;
    }
    if (GuiWindowBox(rec_def, "Definition"))
    {
        selectedWord = NULL;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
        return false;
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

    const int button_width = 100;

    GuiButton({rec_def.x + rec_def.width - 15 - button_width, rec_def.y + rec_def.height - 60, button_width, 45}, "Delete");
    if (!selectedWord->isFavorite)
    {
        GuiDrawIcon(200, 500, 150, 4, BLACK);
        if (GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45 }, "Add Favorite"))
        {
            slang.updateFavorite(selectedWord);
            // just debug
            std::cerr << "Favorite list: ";
            for (auto word : slang.getFavoriteList())
            {
                std::cerr << word->data << ' ';
            }
            std::cerr << std::endl;
        }
    }
    else
    {
        GuiDrawIcon(186, 500, 150, 4, RED);
        if (GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45 }, "Remove Favorite"))
        {
            slang.removeFavorite(selectedWord);
            // just debug
            std::cerr << "Favorite list: ";
            for (auto word : slang.getFavoriteList())
            {
                std::cerr << word->data << ' ';
            }
            std::cerr << std::endl;
        }
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