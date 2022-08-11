#pragma once
#include "home.h"

struct Definitionmenu
{
private:
    void deleteBox(short type);
    void editMenu();
    void editEachDef();
    void addDef();
    void saveBox();

    Rectangle rec_box{ 50, 100, 1100, 500 };
    Rectangle rec_def{ 50, 205, 1100, 300 };
    std::string fullDef = "\0";
    std::vector<std::string> eachDef;
    std::vector<int> edit_height;
    std::vector<bool> editMode;
    std::string tmp, newData, text;
    char newdata[501];
    float propotion, y_coordinate = 200;
    int position, pre, defChosen = -1;
    bool confirmDeleteBox = false, confirmSaveBox = false, editButton = false, editEachDefButton = false, addDefButton = false;
public:
    Definitionmenu();
    ~Definitionmenu()
    {
    }
    Screen update();
    void draw();
};
