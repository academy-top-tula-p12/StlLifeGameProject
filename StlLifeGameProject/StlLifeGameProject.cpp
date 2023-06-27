#include <iostream>
#include "Console.h"
#include "Cell.h"
#include <array>
#include <vector>

using namespace std;

int main()
{
    Console console;

    const int Rows{ 100 };
    const int Cols{ 100 };

    int row = 0;
    int col = 0;

    array<vector<Cell>, 2> colony;
    bool current{ false };

    Key key;
    bool isExit{ false };

    while (true)
    {
        
        if (_kbhit())
        {
            key = (Key)console.ReadKey();
            switch (key)
            {
            case Key::ArrowLeft:
                if (col > 0) col--;
                break;
            case Key::ArrowRight:
                if (col < Cols) col++;
                break;
            case Key::ArrowUp:
                if (row > 0) row--;
                break;
            case Key::ArrowDown:
                if (row < Rows) row++;
                break;
            case Key::Space:
                // установка или отмена установки клетки
                break;
            case Key::Esc:
                isExit = true;
                break;
            case Key::Enter:
                // старт жизни
                isExit = true;
                break;
            default:
                break;
            }
        }
        if (isExit) break;
        console.SetPosition(row, col * 2);
    }


}
