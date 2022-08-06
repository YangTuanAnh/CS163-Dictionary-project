#define _CRT_SECURE_NO_WARNINGS
#include "../../include/raygui.h"
#include "definition.h"

const int button_width = 100;
Definitionmenu::Definitionmenu()
{
}
Screen Definitionmenu::update()
{
    if (confirmDeleteBox || editButton) return DEFINITION;
    if (!selectedWord)
    {
        fullDef = "\0";
        eachDef.clear();
        return HOME;
    }
    if (fullDef == "\0")
    {
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
            eachDef.push_back(tmp);
        }
        rec_def.height = MeasureTextEx(fnt, fullDef.c_str(), 25, 1).y + 20;
    }
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
    if (confirmDeleteBox)
    {
        deleteBox();
        return;
    }
    if (editButton)
    {
        editMenu();
        return;
    }
    DrawTextEx(fnt, fullDef.c_str(), { rec_def.x + 15, rec_def.y }, 25, 1, BLACK);
    DrawRectangleRec({ 52, 124, rec_box.width - 4, 78 }, RAYWHITE);
    DrawRectangleRec({ 52, 520, rec_box.width - 4, 78 }, RAYWHITE);
    if (GuiButton({ rec_box.x + rec_box.width - 15 - button_width, rec_box.y + rec_box.height - 60, button_width, 45 }, "Delete"))
        confirmDeleteBox = true;
    if (!selectedWord->isFavorite)
    {
        GuiDrawIcon(200, 1000, 123, 5, GRAY);
        if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45 }, "Add Favorite"))
            data[*modeChosen].updateFavorite(selectedWord);
    }
    else
    {
        GuiDrawIcon(186, 1000, 123, 5, RED);
        if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45 }, "Remove Favorite"))
            data[*modeChosen].removeFavorite(selectedWord);
    }

    if (GuiButton({ rec_box.x + rec_box.width - (15 + button_width) * 4, rec_box.y + rec_box.height - 60, button_width, 45 }, "Edit"))
    {
        fullDef = "\0";
        editButton = true;
        edit_height.push_back(200);
        for (int i = 1; i <= eachDef.size(); i++)
        {
            edit_height.push_back(MeasureTextEx(fnt, eachDef[i - 1].c_str(), 25, 1).y + edit_height[i - 1] + 35);
        }
        return;
    }
    DrawTextEx(fnt, selectedWord->data.c_str(), { rec_box.x + 15, rec_box.y + 38 }, 45, 2, BLACK);
    DrawRectangleRec({ 51, 100, rec_box.width - 2, 35 }, LIGHTGRAY);
    if (GuiButton({ 1100,100,50,35 }, "X"))
    {
        selectedWord = NULL;
        fullDef = "\0";
        eachDef.clear();
        return;
    }
    DrawRectangleLinesEx({ rec_box }, 2, BLACK);
    DrawLine(50, 135, 1150, 135, BLACK);
}

void Definitionmenu::deleteBox()
{
    if (GuiWindowBox({ 300, 170, 600, 250 }, ""))
        confirmDeleteBox = false;
    std::string text = "Are you sure to delete '" + selectedWord->data + "'?";
    DrawTextEx(fnt, text.c_str(), { 600 - MeasureTextEx(fnt, text.c_str(), 27, 1).x / 2, 220 }, 27, 1, BLACK);
    if (GuiButton({ 400, 330, 100, 50 }, "NO"))
        confirmDeleteBox = false;
    if (GuiButton({ 700, 330, 100, 50 }, "YES"))
    {
        Word* temp = selectedWord;
        selectedWord = nullptr;
        data[*modeChosen].deleteWord(temp);
        confirmDeleteBox = false;
    }
}

void Definitionmenu::saveBox()
{
    if (GuiWindowBox({ 300, 170, 600, 250 }, ""))
        confirmSaveBox = false;
    std::string text = "Save changes in this definition?";
    DrawTextEx(fnt, text.c_str(), { 600 - MeasureTextEx(fnt, text.c_str(), 27, 1).x / 2, 220 }, 27, 1, BLACK);
    if (GuiButton({ 400, 330, 100, 50 }, "Cancel"))
        confirmSaveBox = false;
    if (GuiButton({ 700, 330, 100, 50 }, "Yes"))
    {
        editButton = false;
        for (int i = 0; i < eachDef.size(); i++)
            fullDef += eachDef[i] + "\n";
        confirmSaveBox = false;
        edit_height.clear();
    }
}