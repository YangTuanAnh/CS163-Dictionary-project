#include "game.h"
#include "../../include/raygui.h"
#include "definition.h"

Screen Game::update()
{

    for (int i = 0; i < 4; i++)
        std::cerr << (isWordGame ? quiz[i]->defs[0]->data : quiz[i]->data) << ' ';
    std::cerr << '\n';
    std::cerr << (!isWordGame ? quiz[4]->defs[0]->data : quiz[4]->data) << '\n';

    if (IsMouseButtonPressed(0))
    {
        for (int i = 0; i < 4; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), {(float)320 + 220 * i, 500, 200, 65}))
            {
                pressed = true;
                if (quiz[i]->data == quiz[4]->data)
                {
                    ans = "Correct answer: " + options[i];
                    correctAns = true;
                }
                else
                {
                    ans = "Wrong answer: " + options[i];
                    correctAns = false;
                }
            }
        }
    }

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
    {
        DrawRectangleGradientH(320 + 220 * i, 500, 200, 65, button_color[i][0], button_color[i][1]);
        if (CheckCollisionPointRec(GetMousePosition(), {(float)320 + 220 * i, 500, 200, 65}))
            DrawRectangleGradientH(320 + 220 * i, 500, 200, 65, button_color[i][1], button_color[i][0]);
        DrawTextEx(fnt, options[i].c_str(), {(float)320 + 220 * i + (200 - 40) / 2, (float)500 + (65 - 40) / 2}, 40, 1, WHITE);
    }
    if (pressed)
        DrawTextEx(fnt, ans.c_str(), {320, 145}, 30, 1, correctAns ? GREEN : RED);
}
