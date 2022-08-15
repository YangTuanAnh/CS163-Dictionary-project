#define _CRT_SECURE_NO_WARNINGS
#include "../../include/raygui.h"
#include "definition.h"

const int button_width = 100;
Definitionmenu::Definitionmenu()
{
    for (int i = 0; i < 501; i++)
        newdata[i] = '\0';
}
Screen Definitionmenu::update()
{
    if (confirmDeleteBox || editButton)
        return DEFINITION;
    if (!selectedWord)
    {
        fullDef = "\0";
        eachDef.clear();
        return HOME;
    }
    if (fullDef == "\0")
    {
        for (int j = 0; j < selectedWord->defs.size(); j++)
        {
            tmp = selectedWord->defs[j]->data;
            if (MeasureTextEx(fnt, tmp.c_str(), 25, 1).x > rec_def.width - 20)
            {
                propotion = float(MeasureTextEx(fnt, tmp.c_str(), 25, 1).x / rec_def.width);
                pre = 0;
                position = tmp.length() / (float)propotion;
                while (position < tmp.length())
                {
                    while (position < tmp.length() && MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x < rec_def.width - 20)
                        position++;
                    if (position < tmp.length() - 1)
                        while (tmp[position] != ' ' || MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x > rec_def.width - 20)
                            position--;
                    if (position < tmp.length() - 1)
                        tmp[position] = '\n';
                    pre = position + 2;
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
    if (editButton)
    {
        editMenu();
        return;
    }
    if (confirmDeleteBox)
    {
        deleteBox(-1);
        return;
    }
    DrawTextEx(fnt, fullDef.c_str(), {rec_def.x + 10, rec_def.y}, 25, 1, BLACK);
    DrawRectangleRec({52, 120, rec_box.width - 4, 78}, RAYWHITE);
    DrawRectangleRec({52, 500, rec_box.width - 4, 100}, RAYWHITE);
    if (GuiButton({rec_box.x + rec_box.width - 15 - button_width, rec_box.y + rec_box.height - 60, button_width, 45}, "Delete"))
        confirmDeleteBox = true;
    if (!selectedWord->isFavorite)
    {
        GuiDrawIcon(200, 1080, 163, 3, GRAY);
        if (GuiButton({rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45}, "Add Favorite"))
            data[*modeChosen].updateFavorite(selectedWord);
    }
    else
    {
        GuiDrawIcon(186, 1080, 163, 3, RED);
        if (GuiButton({rec_box.x + rec_box.width - (15 + button_width) * 3, rec_box.y + rec_box.height - 60, button_width * 2 + 15, 45}, "Remove Favorite"))
            data[*modeChosen].removeFavorite(selectedWord);
    }

    if (GuiButton({rec_box.x + rec_box.width - (15 + button_width) * 4, rec_box.y + rec_box.height - 60, button_width, 45}, "Edit"))
    {
        rec_def.y = 205;
        fullDef = "\0";
        editButton = true;
        edit_height.push_back(200);
        for (int i = 1; i <= eachDef.size(); i++)
        {
            edit_height.push_back(MeasureTextEx(fnt, eachDef[i - 1].c_str(), 25, 1).y + edit_height[i - 1] + 35);
        }
        return;
    }
    DrawTextEx(fnt, selectedWord->data.c_str(), {rec_box.x + 15, rec_box.y + 38}, 45, 2, BLACK);
    DrawRectangleGradientH(51, 120, rec_box.width - 2, 35, BLUE, {42, 157, 244, 255});
    if (GuiButton({1100, 120, 50, 35}, "X"))
    {
        rec_def.y = 205;
        selectedWord = NULL;
        fullDef = "\0";
        eachDef.clear();
        return;
    }
    DrawRectangleLinesEx({rec_box}, 1.5, BLACK);
    DrawLine(50, 155, 1150, 155, BLACK);
}

void Definitionmenu::deleteBox(short type) //-1. delete Word, 1. delete Def
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmDeleteBox = false;
    if (type == -1)
        text = "Are you sure to delete '" + selectedWord->data + "'?";
    else
        text = "Are you sure to delete this definition?";
    DrawTextEx(fnt, text.c_str(), {600 - MeasureTextEx(fnt, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "NO"))
        confirmDeleteBox = false;
    if (GuiButton({700, 330, 100, 50}, "YES"))
    {
        if (type == -1)
        {
            rec_def.y = 205;
            Word *temp = selectedWord;
            selectedWord = nullptr;
            data[*modeChosen].deleteWord(temp);
        }
        else
        {
            editEachDefButton = false;
            newData.clear();
            for (int i = 0; i < 501 && newdata[i] != '\0'; i++)
                newdata[i] = '\0';
            y_coordinate = 200;
            confirmDeleteBox = false;
            data[*modeChosen].deleteDef(selectedWord->defs[defChosen]);
            eachDef.erase(eachDef.begin() + defChosen);
            edit_height.push_back(200);
            for (int i = 1; i <= eachDef.size(); i++)
            {
                edit_height.push_back(MeasureTextEx(fnt, eachDef[i - 1].c_str(), 25, 1).y + edit_height[i - 1] + 35);
            }
        }
        confirmDeleteBox = false;
    }
}

void Definitionmenu::editMenu()
{
    if (editEachDefButton)
    {
        editEachDef();
        return;
    }
    if (confirmSaveBox)
    {
        saveBox();
        return;
    }
    if (addDefButton)
    {
        addDef();
        return;
    }
    if (GetMouseWheelMove() == 1 && edit_height[0] < 200)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] += 40;
    }
    if (GetMouseWheelMove() == -1 && edit_height.back() >= 540)
    {
        for (int i = 0; i <= eachDef.size(); i++)
            edit_height[i] -= 40;
    }
    for (int i = 0; i < eachDef.size(); i++)
    {
        DrawTextEx(fnt, eachDef[i].c_str(), {34, (float)edit_height[i] + 8}, 25, 1, BLACK);
        DrawRectangleLinesEx({20, (float)edit_height[i], 1100, (float)edit_height[i + 1] - edit_height[i] - 20}, 2, BLACK);
        if (GuiButton({1130, (float)edit_height[i], 65, 40}, "Edit") && GetMousePosition().y > 200)
        {
            edit_height.clear();
            defChosen = i;
            editEachDefButton = true;
            strcpy(newdata, selectedWord->defs[defChosen]->data.c_str());
            return;
        }
    }
    DrawRectangleRec({0, 100, 1200, 90}, RAYWHITE);
    DrawTextEx(fnt, "EDIT MENU", {70, 130}, 40, 1, RED);
    if (GuiButton({750, 130, 100, 50}, "SAVE"))
        confirmSaveBox = true;
    if (GuiButton({880, 130, 170, 50}, "ADD MORE"))
    {
        addDefButton = true;
        newData = "\0";
        defChosen = eachDef.size();
        newdata[0] = '\0';
    }
}

void Definitionmenu::editEachDef()
{
    if (confirmDeleteBox)
    {
        deleteBox(1);
        return;
    }
    if (GetMouseWheelMove() == 1 && y_coordinate < 200)
        y_coordinate += 30;
    if (GetMouseWheelMove() == -1)
        y_coordinate -= 30;
    GuiTextBoxMulti({50, y_coordinate, 1100, 5000}, newdata, 800, true);
    DrawRectangleRec({0, 100, 1200, 90}, RAYWHITE);
    DrawTextEx(fnt, TextFormat("%i/%i", strlen(newdata), 500), {1080, 150}, 30, 1, LIGHTGRAY);
    DrawTextEx(fnt, "EDIT MENU", {70, 130}, 40, 1, RED);
    if (GuiButton({880, 130, 150, 50}, "DELETE"))
        confirmDeleteBox = true;
    if (GuiButton({750, 130, 100, 50}, "SAVE"))
    {
        newData.clear();
        for (int i = 0; i < 501 && newdata[i] != '\0'; i++)
        {
            newData.push_back(newdata[i]);
            newdata[i] = '\0';
        }
        y_coordinate = 200;
        editEachDefButton = false;
        data[*modeChosen].editDef(selectedWord->defs[defChosen], newData);
        tmp = selectedWord->defs[defChosen]->data;
        if (MeasureTextEx(fnt, tmp.c_str(), 25, 1).x > rec_def.width - 20)
        {
            propotion = float(MeasureTextEx(fnt, tmp.c_str(), 25, 1).x / rec_def.width);
            pre = 0;
            position = tmp.length() / (float)propotion;
            while (position < tmp.length())
            {
                while (position < tmp.length() && MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x < rec_def.width - 20)
                    position++;
                if (position < tmp.length() - 1)
                    while (tmp[position] != ' ' || MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x > rec_def.width - 20)
                        position--;
                if (position < tmp.length() - 1)
                    tmp[position] = '\n';
                pre = position + 2;
                position += tmp.length() / (float)propotion;
            }
        }
        eachDef[defChosen] = tmp;
        edit_height.push_back(200);
        for (int i = 1; i <= eachDef.size(); i++)
        {
            edit_height.push_back(MeasureTextEx(fnt, eachDef[i - 1].c_str(), 25, 1).y + edit_height[i - 1] + 35);
        }
    }
}

void Definitionmenu::addDef()
{
    if (GetMouseWheelMove() == 1 && y_coordinate < 200)
        y_coordinate += 30;
    if (GetMouseWheelMove() == -1)
        y_coordinate -= 30;
    GuiTextBoxMulti({50, y_coordinate, 1100, 5000}, newdata, 800, true);
    DrawRectangleRec({0, 100, 1200, 90}, RAYWHITE);
    DrawTextEx(fnt, TextFormat("%i/%i", strlen(newdata), 500), {950, 140}, 40, 1, LIGHTGRAY);
    DrawTextEx(fnt, "ADD MENU", {70, 130}, 40, 1, RED);
    if (GuiButton({800, 130, 100, 50}, "ADD"))
    {
        newData.clear();
        for (int i = 0; i < 501 && newdata[i] != '\0'; i++)
        {
            newData.push_back(newdata[i]);
            newdata[i] = '\0';
        }
        y_coordinate = 200;
        addDefButton = false;
        data[*modeChosen].insertDef(selectedWord, newData);
        tmp = selectedWord->defs[defChosen]->data;
        if (MeasureTextEx(fnt, tmp.c_str(), 25, 1).x > rec_def.width - 20)
        {
            propotion = float(MeasureTextEx(fnt, tmp.c_str(), 25, 1).x / rec_def.width);
            pre = 0;
            position = tmp.length() / (float)propotion;
            while (position < tmp.length())
            {
                while (position < tmp.length() && MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x < rec_def.width - 20)
                    position++;
                if (position < tmp.length() - 1)
                    while (tmp[position] != ' ' || MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x > rec_def.width - 20)
                        position--;
                if (position < tmp.length() - 1)
                    tmp[position] = '\n';
                pre = position + 2;
                position += tmp.length() / (float)propotion;
            }
        }
        eachDef.push_back(tmp);
        edit_height.push_back(MeasureTextEx(fnt, eachDef.back().c_str(), 25, 1).y + edit_height[eachDef.size() - 1] + 35);
    }
}

void Definitionmenu::saveBox()
{
    if (GuiWindowBox({300, 170, 600, 250}, ""))
        confirmSaveBox = false;
    std::string text = "Save changes in this definition?";
    DrawTextEx(fnt, text.c_str(), {600 - MeasureTextEx(fnt, text.c_str(), 27, 1).x / 2, 220}, 27, 1, BLACK);
    if (GuiButton({400, 330, 100, 50}, "Cancel"))
        confirmSaveBox = false;
    if (GuiButton({700, 330, 100, 50}, "Yes"))
    {
        editButton = false;
        for (int i = 0; i < eachDef.size(); i++)
            fullDef += eachDef[i] + "\n";
        confirmSaveBox = false;
        edit_height.clear();
    }
}