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

ListSimple::ListSimple()
{
    last = NULL;
    size = 0;
}

ListSimple::~ListSimple()
{
    // TODO: libérer l'espace alloué
}
bool ListSimple::isEmpty()
{
    return last == NULL;
}

void ListSimple::display()
{
    if (this->isEmpty())
        return;

    NodeSimple *temp = last;

    while ((temp = temp->getNext()) != last)
    {
        temp->getShape()->display();
    }

    last->getShape()->display();
}

void ListSimple::add(Shape *shape, InsertionDirection direction)
{

    if (last == NULL)
    {
        shape->setCoord(0, PLATEAU_POS_Y); // position initiale
        last = new NodeSimple(shape);
        size++;

        return;
    }

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
        // chainage
        last->setNext(node);

        // mise a jour des coordonnes
        node->getShape()->setCoord(0, PLATEAU_POS_Y);

        NodeSimple *temp = node->getNext();

        while (temp != node)
        {
            temp->getShape()->setCoord(temp->getShape()->getCoord().X + 1, PLATEAU_POS_Y);
            temp = temp->getNext();
        }
    }

    size++; // augmenter la taille de la list
}

void ListSimple::remove(Shape *)
{
}

size_t ListSimple::getSize()
{
    return size;
}
/* Class NodeDouble */

NodeDouble::NodeDouble(NodeSimple *nodee)
{
    this->node = node;
    prev = next = this; // NodeDouble point sur lui meme
}

NodeSimple *NodeDouble::getNode()
{
    return node;
}

void NodeDouble::setPrev(NodeDouble *prev)
{
    this->prev = prev;
}

NodeDouble *NodeDouble::getPrev()
{
    return prev;
}

void NodeDouble::setNext(NodeDouble *next)
{
    this->next = next;
}

NodeDouble *NodeDouble::getNext()
{
    return next;
}

/* Class ListDouble */

ListDouble::ListDouble()
{
    last = NULL;
    size = 0;
}
void ListDouble::add(NodeSimple *node)
{
    NodeDouble *temp = new NodeDouble(node);

    if (last != NULL)
    {
        // chainage temp
        temp->setNext(last->getNext());
        temp->setPrev(last);

        last->setNext(temp);
        last->getNext()->setPrev(temp);
    }

    last = temp;
}
void ListDouble::remove(NodeSimple *node)
{
}

/* class Game */
Game::Game()
{

    // réinitialiser le generateur de nombre aléatoire
    std::srand(std::time(nullptr));

    // initialiser le prochain
    std::cout << "Prochain :";
    this->updateNext();

    // initialiser le plateau
    plateau = new ListSimple();

    std::cout << "\n\n\nPlateau : ";
    plateau->display();
}
Game::~Game()
{
    delete plateau;
}
Shape *Game::randShape()
{
    return new Shape(randForm(), randColor());
}

void Game::updateNext()
{
    next = randShape();
    next->setCoord(11, 0);
    next->display();
}
void Game::insert(InsertionDirection dir)
{
    if (plateau->getSize() == MAX_PLATEAU_SIZE)
    {
        this->displayGameOver();
        return;
    }
    plateau->add(next, dir);
    plateau->display();

    this->updateNext();
}

void Game::displayGameOver()
{

    system("cls");

    std::cout << R"(
   _____                         ____                   _ 
  / ____|                       / __ \                 | |
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __  | |
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__| | |
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |    |_|
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|    (_)
                                                          
                                                          
    )" << std::endl;
}