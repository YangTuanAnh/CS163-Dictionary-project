#include "../../include/raygui.h"
#include "definition.h"

const int button_width = 100;
Definitionmenu::Definitionmenu()
{
}
Screen Definitionmenu::update()
{
    if (!selectedWord) return HOME;
    fullDef = "\0";
    for (int j = 0;j < selectedWord->defs.size();j++)
    {
        tmp = selectedWord->defs[j]->data;
        if (MeasureTextEx(fnt, tmp.c_str(), 25, 1).x > rec_def.width - 20)
        {
            propotion = float(MeasureTextEx(fnt, tmp.c_str(), 25, 1).x / (rec_def.width - 20));
            pre = 0;
            position = tmp.length() / (float)propotion;
            while (position < tmp.length())
            {
                while (tmp[position] != ' ' || MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x > rec_def.width - 20)
                    position--;
                tmp[position] = '\n';
                pre = position + 1;
                position += tmp.length() / (float)propotion;
            }
        }
        fullDef += tmp + "\n";
    }
    rec_def.height = MeasureTextEx(fnt, fullDef.c_str(), 25, 1).y + 20;
    if (GetMouseWheelMove() == -1 && rec_def.y + rec_def.height > 530)
    {
        rec_def.y -= 25;
    }
    if (GetMouseWheelMove() == 1 && rec_def.y < 205)
    {
        rec_def.y += 25;
    }
    return DEFINITION;
}

void Definitionmenu::draw()
{
    
    DrawTextEx(fnt, fullDef.c_str(), { rec_def.x + 15, rec_def.y }, 25, 1, BLACK);
    DrawRectangleRec({ 52, 124, rec_box.width - 4, 78 }, RAYWHITE);
    DrawRectangleRec({ 52, 520, rec_box.width - 4, 78 }, RAYWHITE);
    GuiButton({ rec_box.x + rec_box.width - 15 - button_width, rec_box.y + rec_box.height - 60, button_width, 45 }, "Delete");
    if (!selectedWord->isFavorite)
    {
        GuiDrawIcon(200, 1000, 123, 5, GRAY);
        if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45 }, "Add Favorite"))
            slang.updateFavorite(selectedWord);
    }
    else
    {
        GuiDrawIcon(186, 1000, 123, 5, RED);
        if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45 }, "Remove Favorite"))
            slang.removeFavorite(selectedWord);
    }

    GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 4, rec_box.y + rec_box.height - 60, button_width, 45 }, "Edit");
    DrawTextEx(fnt, selectedWord->data.c_str(), { rec_box.x + 15, rec_box.y + 38 }, 45, 2, BLACK);
    DrawRectangleRec({ 51, 100, rec_box.width - 2, 35 }, LIGHTGRAY);
    if (GuiButton({ 1100,100,50,35 }, "X"))
    {
        rec_def.y = 205;
        selectedWord = NULL;
        fullDef = "\0";
        return;
    }
    DrawRectangleLinesEx({ rec_box }, 2, BLACK);
}