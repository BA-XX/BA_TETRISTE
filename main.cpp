#include "game.hpp"

void showMenu()
{

    std::cout << R"( 
  ____    _      _____ _____ _____ ____  ___ ____ _____ _____ 
 | __ )  / \    |_   _| ____|_   _|  _ \|_ _/ ___|_   _| ____|
 |  _ \ / _ \     | | |  _|   | | | |_) || |\___ \ | | |  _|  
 | |_) / ___ \    | | | |___  | | |  _ < | | ___) || | | |___ 
 |____/_/   \_\___|_| |_____| |_| |_| \_\___|____/ |_| |_____|
             |_____|                                          

  @BA_XX         
)" << std::endl;
}

int main()
{
    Game game;

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
        }
    }

    return 0;
}
