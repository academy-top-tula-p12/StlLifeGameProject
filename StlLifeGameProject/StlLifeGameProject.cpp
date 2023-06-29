#include "LifeGame.h"
#include <thread>

using namespace std;

int main()
{
    LifeGame game;
    bool play = game.SetColony();
    if (!play) return 0;

    Key key;
    game.CursorOff();
    while (true)
    {
        if (_kbhit() && (Key)_getch() == Key::Esc) break;
        game.Generate();
        game.ColonyShow();
        //game.Wait();
        this_thread::sleep_for(1000ms);
    }
    game.CursorOn();
}
