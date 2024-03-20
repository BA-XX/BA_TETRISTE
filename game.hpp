#pragma once

#include "utils.hpp"

const short PLATEAU_POS_Y = 2; // definir l'emplacement

enum Form
{
    square = 'S',
    triangle = 'T',
    circle = 'C',
    diamond = 'D'
};

enum Color
{
    red = FOREGROUND_RED,
    blue = FOREGROUND_BLUE,
    yellow = FOREGROUND_RED | FOREGROUND_GREEN,
    green = FOREGROUND_GREEN
};

enum InsertionDirection
{
    INSERT_RIGHT,
    INSERT_LEFT
};

class Shape
{
private:
    Form form;
    Color color;
    COORD coord; // {X , Y}

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
    ListSimple(Shape *);
    bool isEmpty();
    void display();
    void add(Shape *, InsertionDirection = INSERT_RIGHT);
    void remove(Shape *);
};

class NodeDouble
{
    Shape *shape;
    NodeDouble *prev;
    NodeDouble *next;

public:
    NodeDouble(Shape *);
    NodeDouble(Shape *, NodeDouble *, NodeDouble *);

    Shape* getShape();
    NodeDouble *getPrev();
    NodeDouble *getNext();
};

class ListDouble
{

    NodeDouble *first;
    size_t size;

public:
    ListDouble(Shape *);
    void add(Shape *);
    void remove(Shape *);
};