#include "../../include/raygui.h"
#include "definition.h"

const int button_width = 100;
Definitionmenu::Definitionmenu()
{
}
Screen Definitionmenu::update()
{
    fullDef = "\0";
    if (!selectedWord) return HOME;
    return DEFINITION;
}

void Definitionmenu::draw()
{
    if (GuiWindowBox(rec_box, "Definition"))
    {
        selectedWord = NULL;
        fullDef = "\0";
        return;
    }
    GuiButton({ rec_box.x + rec_box.width - 15 - button_width, rec_box.y + rec_box.height - 60, button_width, 45 }, "Delete");
    if (!selectedWord->isFavorite)
    {
        GuiDrawIcon(200, 1000, 140, 5, GRAY);
        if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45 }, "Add Favorite"))
            slang.updateFavorite(selectedWord);
    }
    else
    {
        GuiDrawIcon(186, 1000, 140, 5, RED);
        if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45 }, "Remove Favorite"))
            slang.removeFavorite(selectedWord);
    }

    GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 4, rec_box.y + rec_box.height - 60, button_width, 45 }, "Edit");

    DrawTextEx(fnt, selectedWord->data.c_str(), { rec_box.x + 15, rec_box.y + 40 }, 40, 2, BLACK);
    for (int j = 0; j < selectedWord->defs.size(); j++)
    {
        std::string s = selectedWord->defs[j]->data;
        if (s.length() * 10 > rec_box.width - 15)
        {
            int len = (rec_box.width - 15) / 10, temp = len;
            while (temp < s.length())
            {
                while (s[temp] != ' ' && temp < s.length())
                    temp--;
                s.insert(s.begin() + temp, '\n');
                temp += len;
            }
        }
        s.push_back('\n');
        fullDef += s;
    }
    DrawTextEx(fnt, fullDef.c_str(), { rec_def.x + 15, rec_def.y }, 22, 1.5, BLACK);
}