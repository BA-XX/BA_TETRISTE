#include "game.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/* Class Shape */
Shape::Shape(Form form, Color color, short x, short y)
{
    this->form = form;
    this->color = color;
    coord = {x, y};
}

void Shape::display()
{

    // Change la couleur du texte
    SetConsoleTextAttribute(hConsole, color);
    // Déplacer le curseur
    SetConsoleCursorPosition(hConsole, coord);

    std::cout << (char)form;
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
    this->coord = {x, y}; // changer les coordonee
    this->remove();       // effacer
    this->display();      // afficher
}

Color Shape::getColor()
{
    return color;
}

/* Class NodeSimple */

NodeSimple::NodeSimple(Shape *shape)
{
    this->shape = shape;
    this->next = this;
}
NodeSimple::NodeSimple(Shape *shape, NodeSimple *next)
{
    this->shape = shape;
    this->next = next;
}
Shape *NodeSimple::getShape()
{
    return shape;
}
void NodeSimple::setNext(NodeSimple *next)
{
    this->next = next;
}
NodeSimple *NodeSimple::getNext()
{
    return next;
}

/* Class ListSimple */

ListSimple::ListSimple(Shape *shape)
{
    shape->setCoord(0, PLATEAU_POS_Y); // position initiale

    last = new NodeSimple(shape);

    size = 1;
}

bool ListSimple::isEmpty()
{
    return last == NULL;
}

void ListSimple::display()
{
    if (this->isEmpty())
    {
        std::cout << "IS EMPTY " << this->isEmpty();
        return;
    }

    NodeSimple *temp = last;

    while ((temp = temp->getNext()) != last)
    {
        temp->getShape()->display();
    }

    last->getShape()->display();
}

void ListSimple::add(Shape *shape, InsertionDirection direction)
{

    // creation d'une nouveau node simple
    NodeSimple *node = new NodeSimple(shape, last->getNext()); // last->getNext() retourn le premier de la list

    if (direction == INSERT_RIGHT) // insertion a droit
    {
        // mise a jour des coordonnes
        node->getShape()->setCoord(last->getShape()->getCoord().X + 1, PLATEAU_POS_Y);

        // chainage
        last->setNext(node);
        last = node; // changer la valeur du pointeur vers le dernier element
    }
    else // insertion a gauche
    {
        // mise a jour des coordonnes
        node->getShape()->setCoord(0, PLATEAU_POS_Y);
        last->getShape()->setCoord(1, PLATEAU_POS_Y);

        // chainage
        last->setNext(node);
    }

    size++; // augmenter la taille de la list
}

void ListSimple::remove(Shape *)
{
}

/* Class NodeDouble */

NodeDouble::NodeDouble(Shape *shape)
{
    this->shape = shape;
    prev = next = this; // NodeDouble point sur lui meme
}
NodeDouble::NodeDouble(Shape *shape, NodeDouble *prev, NodeDouble *next)
{
    this->shape = shape;
    this->prev = prev;
    this->next = next;
}

Shape *NodeDouble::getShape()
{
    return shape;
}

NodeDouble *NodeDouble::getPrev()
{
    return prev;
}
NodeDouble *NodeDouble::getNext()
{
    return next;
}

/* Class ListDouble */

ListDouble::ListDouble(Shape *shape)
{
}
void ListDouble::add(Shape *shape)
{
}
void ListDouble::remove(Shape *shape)
{
}