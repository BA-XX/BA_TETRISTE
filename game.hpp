#pragma once

#include "utils.hpp"

const short PLATEAU_POS_Y = 4; // definir l'emplacement du plateau
const short MAX_PLATEAU_SIZE = 15;

class Shape
{
private:
    Form form;
    Color color;
    COORD coord; // struct COORD { short X , short Y}

public:
    Shape(Form, Color, short x = 0, short y = 0);
    void display();
    void remove();

    void setCoord(short x, short y);
    COORD getCoord();

    void move(short x, short y = 0);
    Color getColor();
};

class NodeSimple
{

    Shape *shape;
    NodeSimple *next;

public:
    NodeSimple(Shape *);
    NodeSimple(Shape *, NodeSimple *);

    Shape *getShape();

    void setNext(NodeSimple *);
    NodeSimple *getNext();
};

class ListSimple
{

    NodeSimple *last; // pointeur sur le dernier élément de la liste
    size_t size;      // le nombre d'élémetns
public:
    ListSimple();
    ~ListSimple();

    bool isEmpty();
    void display();
    void add(Shape *, InsertionDirection);
    void remove(Shape *);

    size_t getSize();
};

class NodeDouble
{
    NodeSimple *node;
    NodeDouble *prev;
    NodeDouble *next;

public:
    NodeDouble(NodeSimple *);

    NodeSimple *getNode();

    void setPrev(NodeDouble *);
    NodeDouble *getPrev();

    void setNext(NodeDouble *);
    NodeDouble *getNext();
};

class ListDouble
{

    NodeDouble *last;
    size_t size;

public:
    ListDouble();
    void add(NodeSimple *);
    void remove(NodeSimple *);
};

class Game
{
    Shape *next;
    ListSimple *plateau;
    ListDouble *forms[4];  // Tableau de pointeurs vers les listes des pièces ayant la même forme sur le plateau
    ListDouble *colors[4]; // Tableau de pointeurs vers les listes des pièces ayant la même couleur sur le plateau

public:
    Game(); // initialisation du jeu
    ~Game();
    Shape *randShape();

    void updateNext();

    void insert(InsertionDirection = INSERT_RIGHT);

    void displayGameOver();
};