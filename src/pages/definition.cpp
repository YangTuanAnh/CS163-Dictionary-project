#include "definition.h"
#include "../../include/raygui.h"
Rectangle rec_def{ 340, 125, 835, 450 };
bool definitionPage(Word*& word)
{
    if (!word) return false;
    if (GuiWindowBox(rec_def, "Definition"))
    {
        word = NULL;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
        return false;
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

    const int button_width = 100;

    GuiButton({ rec_def.x + rec_def.width - 15 - button_width, rec_def.y + rec_def.height - 60, button_width, 45 }, "Delete");
    if (!word->isFavorite)
    {
        GuiDrawIcon(200, 1000, 150, 5, GRAY);
        if (GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45 }, "Add Favorite"))
        {
            slang.updateFavorite(word);
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
        GuiDrawIcon(186, 1000, 150, 5, RED);
        if (GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45 }, "Remove Favorite"))
        {
            slang.removeFavorite(word);
            // just debug
            std::cerr << "Favorite list: ";
            for (auto word : slang.getFavoriteList())
            {
                std::cerr << word->data << ' ';
            }
            std::cerr << std::endl;
        }
    }

    GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 4, rec_def.y + rec_def.height - 60, button_width, 45 }, "Edit");

    DrawTextEx(fnt, word->data.c_str(), { rec_def.x + 15, rec_def.y + 40 }, 40, 2, BLACK);
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
        DrawTextEx(fnt, s.c_str(), { rec_def.x + 15, rec_def.y + 60 + 30 * cnt }, 20, 2, BLACK);
        cnt += extended;
    }
    return true;
}