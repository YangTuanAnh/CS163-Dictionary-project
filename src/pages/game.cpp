#include "game.h"
#include "../../include/raygui.h"
#include "definition.h"

Screen Game::update()
{

    for (int i = 0; i < 4; i++)
        std::cerr << (isWordGame ? quiz[i]->defs[0]->data : quiz[i]->data) << ' ';
    std::cerr << '\n';
    std::cerr << (!isWordGame ? quiz[4]->defs[0]->data : quiz[4]->data) << '\n';
    if (menuChosen != 4)
    {
        short tmp = menuChosen;
        menuChosen = 4;
        return static_cast<Screen>(tmp);
    }
    return GAME;
}

void Game::draw()
{
    for (int i = 0; i < 5; i++)
        if (GuiButton(rec_modes[i], modes[i].c_str()))
            menuChosen = i;
    std::string options[] = {"A", "B", "C", "D"};

    if (isWordGame)
    {
        DrawTextEx(fnt, quiz[4]->data.c_str(), {320, 200}, 45, 2, BLACK);

        std::string fullOptions = "\0";
        Rectangle rec_def = {320, 250, 1000, 300};
        for (int j = 0; j < 4; j++)
        {
            std::string tmp = quiz[j]->defs[0]->data;
            fullOptions += options[j] + ". ";
            if (MeasureTextEx(fnt, tmp.c_str(), 25, 1).x > 760)
            {
                float propotion = float(MeasureTextEx(fnt, tmp.c_str(), 25, 1).x / (rec_def.width - 20));
                int pre = 0;
                int position = tmp.length() / (float)propotion;
                while (position < tmp.length())
                {
                    while (tmp[position] != ' ' || MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 25, 1).x > rec_def.width - 20)
                        position--;
                    tmp[position] = '\n';
                    pre = position + 1;
                    position += tmp.length() / (float)propotion;
                }
            }
            fullOptions += tmp + "\n";
        }
        DrawTextEx(fnt, fullOptions.c_str(), {rec_def.x + 15, rec_def.y}, 20, 1, BLACK);
        if (GuiButton(rec_gamemode, "Definitions"))
        {
            isWordGame ^= 1;
            quiz = data[*modeChosen].generateRandQuiz();
            pressed = false;
        }
    }
    else
    {
        std::string fullWord = "\0";
        Rectangle rec_word = {320, 200, 800, 150};
        std::string tmp = quiz[4]->defs[0]->data;
        if (MeasureTextEx(fnt, tmp.c_str(), 30, 1).x > 760)
        {
            float propotion = float(MeasureTextEx(fnt, tmp.c_str(), 30, 1).x / (rec_word.width));
            int pre = 0;
            int position = tmp.length() / (float)propotion;
            while (position < tmp.length())
            {
                while (tmp[position] != ' ' || MeasureTextEx(fnt, tmp.substr(pre, position - pre).c_str(), 30, 1).x > rec_word.width)
                    position--;
                tmp[position] = '\n';
                pre = position + 1;
                position += tmp.length() / (float)propotion;
            }
        }
        fullWord += tmp + "\n";
        DrawTextEx(fnt, fullWord.c_str(), {320, 200}, 30, 1, BLACK);

        std::string fullOptions = "\0";
        Rectangle rec_def = {320, 360, 1000, 300};
        for (int j = 0; j < 4; j++)
            fullOptions += options[j] + ". " + quiz[j]->data + '\n';
        DrawTextEx(fnt, fullOptions.c_str(), {rec_def.x + 15, rec_def.y}, 20, 1, BLACK);
        if (GuiButton(rec_gamemode, "Words"))
        {
            isWordGame ^= 1;
            quiz = data[*modeChosen].generateRandQuiz();
            pressed = false;
        }
    }
    if (GuiButton(rec_next, "Next"))
    {
        quiz = data[*modeChosen].generateRandQuiz();
        pressed = false;
    }

    for (int i = 0; i < 4; i++)
        if (GuiButton({(float)320 + 220 * i, 500, 200, 65}, options[i].c_str()))
        {
            pressed = true;
            if (quiz[i]->data == quiz[4]->data)
            {
                ans = "Correct answer: " + options[i];
                correctAns = true;
            }
            else
            {
                ans = "Wrong answer";
                correctAns = false;
            }
        }
    if (pressed)
        DrawTextEx(fnt, ans.c_str(), {320, 145}, 30, 1, correctAns ? GREEN : RED);
}
