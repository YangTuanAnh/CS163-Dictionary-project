#define _CRT_SECURE_NO_WARNINGS
#define RAYGUI_IMPLEMENTATION
#include "../../include/raygui.h"
#include "home.h"
#include "definition.h"

Word *selectedWord = NULL;
Home::Home()
{
    modeChosen = new int(0);
    char **icon = GuiLoadIcons("../data/icons.rgi", true);
    for (int i = 0; i < 20; i++)
        rec_result[i] = {320, (float)200 + 125 * i, 830, 120};
    for (int i = 0; i < 5; i++)
        rec_modes[i] = {30, (float)125 + 90 * i, 245, 60};
    rec_modes[menuChosen] = {20, (float)115 + 90 * menuChosen, 265, 80};
}

Screen Home::update()
{
    word = slang.SearchWord(SearchInput);
    if (GetMouseWheelMove() == -1 && rec_result[word.size() - 1].y > 475)
    {
        for (int i = 0; i < word.size(); i++)
        {
            rec_result[i].y -= 40;
        }
    }
    else if (GetMouseWheelMove() == 1 && rec_result[0].y < 200)
    {
        for (int i = 0; i < word.size(); i++)
        {
            rec_result[i].y += 40;
        }
    }
    if (IsMouseButtonPressed(0) && !dropDowmBox)
    {
        for (int i = 0; i < word.size(); i++)
        {
            if (SearchInput[0] == '\0' && CheckCollisionPointRec(GetMousePosition(), {rec_result[i].x + 750, rec_result[i].y + 5, 32, 32}))
            {
                slang.updateHistory(word[i], false);
                break;
                ;
            }
            else if (CheckCollisionPointRec(GetMousePosition(), {rec_result[i].x + 790, rec_result[i].y + 5, 32, 32}))
            {
                strncpy(SearchInput, word[i]->data.c_str(), sizeof(word[i]->data));
                break;
            }
            else if (GetMousePosition().y > 180 && CheckCollisionPointRec(GetMousePosition(), rec_result[i]))
            {
                selectedWord = word[i];
                slang.getFullDefinition(selectedWord->data);

                for (int i = 0; i < 20; i++)
                    rec_result[i] = {320, (float)200 + 125 * i, 830, 120};
                return DEFINITION;
            }
        }
    }

    if (SearchEdit)
    {
        word = slang.SearchWord(SearchInput);
        if (GetKeyPressed())
        {
            for (int i = 0; i < 20; i++)
                rec_result[i] = {320, (float)200 + 125 * i, 830, 120};
        }
    }

    if (menuChosen)
    {
        short tmp = menuChosen;
        menuChosen = 0;
        return static_cast<Screen>(tmp);
    }
    return HOME;
}

void Home::draw()
{
    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < 5; i++)
    {
        if (GuiButton(rec_modes[i], modes[i].c_str()))
            menuChosen = i;
    }
    for (int i = 0; i < word.size(); i++)
    {
        DrawRectangleRec(rec_result[i], DARKBLUE);
        if (SearchInput[0] == '\0' && CheckCollisionPointRec(mousePos, {rec_result[i].x + 750, rec_result[i].y + 5, 32, 32}))
            GuiDrawIcon(202, rec_result[i].x + 750, rec_result[i].y + 5, 2, RED);
        else if (CheckCollisionPointRec(mousePos, {rec_result[i].x + 790, rec_result[i].y + 5, 32, 32}))
            GuiDrawIcon(201, rec_result[i].x + 790, rec_result[i].y + 5, 2, GREEN);
        else
        {
            if (CheckCollisionPointRec(mousePos, rec_result[i]) && mousePos.y > 180 && !dropDowmBox)
                DrawRectangleRec(rec_result[i], BLUE);
            if (SearchInput[0] == '\0')
                GuiDrawIcon(202, rec_result[i].x + 750, rec_result[i].y + 5, 2, WHITE);
            GuiDrawIcon(201, rec_result[i].x + 790, rec_result[i].y + 5, 2, WHITE);
        }
        if (word[i]->isFavorite)
            GuiDrawIcon(186, rec_result[i].x + 700, rec_result[i].y - 5, 3, RED);
        else
            GuiDrawIcon(200, rec_result[i].x + 700, rec_result[i].y - 5, 3, BLACK);
        DrawTextEx(fnt, word[i]->data.c_str(), {rec_result[i].x + 10, rec_result[i].y + 10}, 34, 2, WHITE);
        for (int j = 0; j < std::min(2, int(word[i]->defs.size())); j++)
        {
            std::string s = word[i]->defs[j]->data;
            if (s.length() * 13 > rec_result[i].width - 13)
            {
                for (int k = 0; k < 3; k++)
                    s.insert(s.begin() + rec_result[i].width / 13 + k, '.');
                s.insert(s.begin() + rec_result[i].width / 13 + 3, '\0');
            }
            DrawTextEx(fnt, s.c_str(), {rec_result[i].x + 15, rec_result[i].y + 35 * j + 50}, 25, 2, LIGHTGRAY);
        }
    }
    DrawRectangle(310, 100, 850, 90, RAYWHITE);
    DrawRectangleLinesEx(rec_search, 3, GREEN);
    if (GuiTextBox(rec_search, SearchInput, 20, SearchEdit))
    {
        for (int i = 0; i < 20; i++)
            rec_result[i] = {320, (float)200 + 125 * i, 830, 120};
        SearchEdit ^= 1;
    }
    if (GuiDropdownBox(rec_dictionary, (dictionary[0] + "\n" + dictionary[1] + "\n" + dictionary[2] + "\n" + dictionary[3]).c_str(), modeChosen, dropDowmBox))
        dropDowmBox ^= 1;
    if (SearchInput[0] == '\0')
        DrawText("Search bar", 333, 135, 30, LIGHTGRAY);
    if (GuiButton(rec_random, "RANDOM"))
    {
        std::string random = slang.getRandomWord();
        for (int i = 0; i < random.length(); i++)
            SearchInput[i] = random[i];
        SearchInput[random.length()] = '\0';
    }
}
