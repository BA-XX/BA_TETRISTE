#include "../game.hpp"

Shape::Shape(Form form, Color color, short x, short y)
{
    this->form = form;
    this->color = color;
    coord = {x, y};
}

Shape::~Shape()
{
    //remove(); // enlever le point du console
}

void Shape::display()
{

    // Change la couleur du texte
    SetConsoleTextAttribute(hConsole, convertToColorCode(color));
    // Déplacer le curseur
    SetConsoleCursorPosition(hConsole, coord);

    std::cout << convertFormToSymbole(form);
    // Rétablit les attributs de couleur d'origine
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

COORD Shape::getCoord()
{
    return coord;
}

void Shape::move(short x, short y)
{
    if (x < 0 || y < 0)
    {
        std::cout << "\n\n\n\nnegative";
        return;
    }

    this->remove();       // effacer
    this->coord = {x, y}; // changer les coordonee
    this->display();      // afficher
}

Color Shape::getColor()
{
    return color;
}
Form Shape::getForm()
{
    return form;
}