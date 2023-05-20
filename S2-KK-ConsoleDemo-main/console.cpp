#include "console.h"
#include <Windows.h>
#include <iostream>
#include <string>

void Console::gotoxy(short x, short y)
{
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

Console::Console(int w, int h)
{
    width = w;
    height = h;
    gotoxy(width+1, width + 1);
    gotoxy(0, 0);
    showCursor(false);
    currentLevel = 0;
}

Console::~Console()
{
    gotoxy(width + 1, width + 1);
    std::cout << std::endl;
    showCursor(true);
}

void Console::display(std::string content)
{
    const char* tab = content.c_str();
    size_t size = content.size();
    size_t h = height;
    size_t w = width;
    gotoxy(0, 0);
    drawHorizontalBar();
    for (size_t i = 0; i < h; i++)
    {
        int posY = static_cast<short>(i);
        gotoxy(0, posY+1);
        std::cout << '#';
        for (size_t j = 0; j < w; j++)
        {
            size_t index = i * w + j;
            if (index < size) 
            {
                std::cout << tab[index];
            }
            else {
                std::cout << ' ';
            }
            
        }
        std::cout << '#';
    }
    gotoxy(0, height+1);
    drawHorizontalBar();
    std::cout << '\n' << std::endl;
    std::cout << "         Le niveau actuel est: " << currentLevel + 1 << std::endl;
    std::cout << "         Le score du joueur est: " << score << "      " << std::endl;
    std::cout << "         Le meilleur score est: " << leaderboard.getHighestScore() << "      " << std::endl;
    //if (score == 20 || score==60||score==120||score==200||score==320) {
        //std::cout << "         Félicitations, nouveau niveau" << std::endl;
    //}
}

void Console::drawHorizontalBar()
{
    for (int i = 0; i < width + 2; i++)
    {
        std::cout << '#';
    }
}

void Console::showCursor(bool show)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
