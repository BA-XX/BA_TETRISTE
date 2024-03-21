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
    coord.X = x;
    coord.Y = y;
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
Form Shape::getForm()
{
    return form;
}

/* Class NodeSimple */

NodeSimple::NodeSimple(Shape *shape)
{
    this->shape = shape;
    this->next = this;
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

void ListSimple::add(NodeSimple *node, InsertionDirection direction)
{

    if (last == NULL)
    {
        node->getShape()->setCoord(0, PLATEAU_POS_Y); // position initiale
        last = node;
        size++;

        return;
    }

    node->setNext(last->getNext()); // last->getNext() retourn le premier de la list

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

void ListSimple::remove(NodeSimple *node)
{
}

size_t ListSimple::getSize()
{
    return size;
}
/* Class NodeDouble */

NodeDouble::NodeDouble(NodeSimple *node)
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
bool ListDouble::isEmpty()
{
    return last == NULL;
}
void ListDouble::add(NodeSimple *node, InsertionDirection dir)
{

    NodeDouble *temp = new NodeDouble(node);

    if (isEmpty())
    {
        last = temp;
        size = 1;
        return;
    }

    // chainage temp
    temp->setNext(last->getNext());
    temp->setPrev(last);

    last->setNext(temp);

    if (dir == INSERT_RIGHT)
    {
        last->getNext()->setPrev(temp);
        last = temp;
    }

    size++;
}
void ListDouble::remove(NodeSimple *node)
{
}

NodeDouble *ListDouble::getLast()
{
    return last;
}

size_t ListDouble::getSize()
{
    return size;
}

bool ListDouble::hasConsecutiveForms()
{
    if (isEmpty())
        return false;

    NodeDouble *temp = last->getNext(); // get the first element

    do
    {
        if (abs((temp->getNode()->getShape()->getCoord().X) - (temp->getNext()->getNode()->getShape()->getCoord().X)) != 1)
            return false;

    } while ((temp = temp->getNext()) != last);

    return true;
}

/* class Game */
Game::Game()
{

    for (int i = 0; i < 4; i++)
    { // allocation de memoire
        listForms[i] = new ListDouble();
        listColors[i] = new ListDouble();
    }

    // réinitialiser le generateur de nombre aléatoire
    std::srand(std::time(nullptr));

    // initialiser le prochain
    std::cout << "Prochain :";
    this->updateNextShape();

    // initialiser le plateau
    plateau = new ListSimple();

    std::cout << "\n\n\nPlateau : ";
    plateau->display();
}
Game::~Game()
{
    delete plateau;

    for (int i = 0; i < 4; i++)
    { // liberation de la memoire
        delete listForms[i];
        delete listColors[i];
    }
}
Shape *Game::randShape()
{
    return new Shape(randForm(), randColor());
}

void Game::start()
{
    system("cls");
}

void Game::updateNextShape()
{
    nextShape = randShape();
    nextShape->setCoord(11, 0);
    nextShape->display();
}
void Game::insert(InsertionDirection dir)
{
    if (plateau->getSize() == MAX_PLATEAU_SIZE)
    {
        this->displayGameOver();
        return;
    }

    NodeSimple *temp = new NodeSimple(nextShape);

    listForms[nextShape->getForm()]->add(temp, dir);
    listColors[nextShape->getColor()]->add(temp, dir);

    plateau->add(temp, dir);
    plateau->display();

    // Déplacer le curseur
    SetConsoleCursorPosition(hConsole, {0, 8});
    std::cout << "Count Form(" << convertFormToSymbole(nextShape->getForm()) << ") : " << listForms[nextShape->getForm()]->getSize();

    std::cout << "\nCount Color(" << nextShape->getColor() << ") : " << listColors[nextShape->getColor()]->getSize();

    std::cout << "\nHas consecutive Froms :" << listForms[nextShape->getForm()]->hasConsecutiveForms();

    this->updateNextShape();
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