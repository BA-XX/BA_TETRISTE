#include "game.hpp"

int main()
{

    ListSimple plateau;

    Game game;

    game.displayMenu();

    while (char c = getch())
    {
        switch (c)
        {
        case 103: // g
            game.insert(INSERT_LEFT);
            break;
        case 100:          // d
            game.insert(); // par default INSERT_RIGHT
            break;
        case 115: // s
            game.leftShiftForms(square);
            break;
        }
    }

    return 0;
}
