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

Color randColor()
{
    int rand = std::rand() % 4; // 4 car nous avons 4 choix enum enter 0 a 4-1 = 3

    switch (rand)
    {
    case 0:
        return red;
        break;
    case 1:
        return blue;
        break;
    case 2:
        return yellow;
        break;
    case 3:
        return green;
        break;
    }
    return red;
}
Form randForm()
{
    int rand = std::rand() % 4; // 4 car nous avons 4 choix enum enter 0 a 4-1 = 3

    switch (rand)
    {
    case 0:
        return square;
        break;
    case 1:
        return triangle;
        break;
    case 2:
        return circle;
        break;
    case 3:
        return diamond;
        break;
    }
    return square;
}

Shape *randShape()
{
    return new Shape(randForm(), randColor());
}
int main()
{

     ListSimple list(randShape());

    for(int i = 0 ; i < 30 ; i++){
        list.add(randShape());
    }

     list.display();

    // showMenu();
    getch();
    return 0;
}
