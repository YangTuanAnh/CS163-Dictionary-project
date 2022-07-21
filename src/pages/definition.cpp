#include "definition.h"
#include "../../include/raygui.h"

const int button_width = 100;
Screen Definitionmenu::update()
{
    if (!selectedWord) return HOME;
    return DEFINITION;
}

void Definitionmenu::draw()
{
    if (GuiWindowBox(rec_def, "Definition"))
    {
        selectedWord = NULL;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
        return;
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

    GuiButton({ rec_def.x + rec_def.width - 15 - button_width, rec_def.y + rec_def.height - 60, button_width, 45 }, "Delete");
    if (!selectedWord->isFavorite)
    {
        GuiDrawIcon(200, 1060, 140, 5, GRAY);
        if (GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45 }, "Add Favorite"))
            slang.updateFavorite(selectedWord);
    }
    else
    {
        GuiDrawIcon(186, 1060, 140, 5, RED);
        if (GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 3, rec_def.y + rec_def.height - 60, button_width * 2 + 15, 45 }, "Remove Favorite"))
            slang.removeFavorite(selectedWord);
    }

    GuiButton({ rec_def.x + rec_def.width - (15 + button_width) * 4, rec_def.y + rec_def.height - 60, button_width, 45 }, "Edit");

    DrawTextEx(fnt, selectedWord->data.c_str(), { rec_def.x + 15, rec_def.y + 40 }, 40, 2, BLACK);
    int cnt = 1;
    for (int j = 0; j < selectedWord->defs.size(); j++)
    {
        std::string s = selectedWord->defs[j]->data;
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
}