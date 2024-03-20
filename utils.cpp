#include "utils.hpp"

int randNumber(int min, int max)
{
    return min + std::rand() % (max - min + 1);
}

Color randColor()
{
    int rand = randNumber(1, 4); // nous avons 4 choix enum

    switch (rand)
    {
    case 1:
        return red;
        break;
    case 2:
        return blue;
        break;
    case 3:
        return yellow;
        break;
    case 4:
        return green;
        break;
    }
    return red;
}
Form randForm()
{
    int rand = randNumber(1, 4); // nous avons 4 choix enum

    switch (rand)
    {
    case 1:
        return square;
        break;
    case 2:
        return triangle;
        break;
    case 3:
        return circle;
        break;
    case 4:
        return diamond;
        break;
    }
    return square;
}
