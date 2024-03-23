#pragma once

#include "utils.hpp"

const short PLATEAU_POS_Y = 4; // definir l'emplacement du plateau
const short MAX_PLATEAU_SIZE = 15;
const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class Shape
{
private:
    Form form;
    Color color;
    COORD coord; // struct COORD { short X , short Y}

public:
    Shape(Form, Color, short x = 0, short y = 0);
    ~Shape();
    void display();
    void remove();

    void setCoord(short x, short y);
    COORD getCoord();

    void move(short x, short y = 0);
    Color getColor();
    Form getForm();
};

class NodeSimple
{

    Shape *shape;
    NodeSimple *next;

public:
    NodeSimple(Shape *);
    ~NodeSimple();

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
    void add(NodeSimple *, InsertionDirection);
    void remove(NodeSimple *);

    bool isLast(NodeSimple *);

    NodeSimple *findPrev(NodeSimple *);

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
    bool isEmpty();
    bool isLast(NodeDouble *);

    void add(NodeSimple *, InsertionDirection = INSERT_RIGHT);
    void remove(NodeDouble *);

    void removeByNode(NodeSimple *);
    NodeDouble *findByNode(NodeSimple *);

    NodeDouble *getLast();

    size_t getSize();
};

class Game
{
    Shape *nextShape;
    ListSimple *plateau;
    ListDouble *listForms[4];  // Tableau de pointeurs vers les listes des pièces ayant la même forme sur le plateau
    ListDouble *listColors[4]; // Tableau de pointeurs vers les listes des pièces ayant la même couleur sur le plateau
    unsigned int score;

    void removeNode(NodeDouble *);
    bool isConsecutive(Shape *, Shape *);
    void checkConsecutive(ListDouble *list);

public:
    Game(); // initialisation du jeu
    ~Game();

    void start(); // lancer un nouveau jeu

    Shape *randShape();

    void updateNextShape();
    void updateScore(unsigned int increase);

    void insert(InsertionDirection = INSERT_RIGHT);

    void displayGameOver();
};