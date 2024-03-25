#include "../game.hpp"

Shape::Shape(Form form, Color color, short x, short y)
{
    this->form = form;
    this->color = color;
    coord = {x, y};
}

Shape::~Shape()
{
    // remove(); // enlever le point du console
}

void Shape::display()
{
    printWithColorAt(convertFormToSymbole(form), convertToColorCode(color), coord);
}

void Shape::remove()
{
    // Déplacer le curseur
    SetConsoleCursorPosition(hConsole, coord);
    std::cout << ' ';
}

void Shape::setCoord(short x, short y)
{
    coord = {x, y};
}
void Shape::setCoord(COORD coord)
{
    this->coord = coord;
}
COORD Shape::getCoord()
{
    return coord;
}

void Shape::move(short x, short y)
{
    if (x < 0 || y < 0)
    {
        std::cout << "\n\n\n\nnegative + " << convertFormToSymbole(form);
        return;
    }

    this->remove();       // effacer
    this->coord = {x, y}; // changer les coordonee
    this->display();      // afficher
}

void Shape::exchangeWith(Shape *shape) // échanger la piece invoqué avec une autre
{
    COORD temp = shape->getCoord();

    shape->setCoord(coord);
    shape->display();

    coord = temp;
    display();
}
Color Shape::getColor()
{
    return color;
}
Form Shape::getForm()
{
    return form;
}