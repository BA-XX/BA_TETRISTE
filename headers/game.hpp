#pragma once

#include "utils.hpp"

const short MAX_PLATEAU_SIZE = 15;
const short MAX_CONSECUTVIES_PIECES = 3;
const short SCORE_REWARD_COEFFICIENT = 10; // coefficient multiplicateur pour chaque pièce consécutive éliminée

const String SCORE_FILE_PATH = "data/scores";
const String MENU_FILE_PATH = "static/menu";
const String PLATEAU_FILE_PATH = "static/plateau";
const String RULES_FILE_PATH = "static/rules";
const String TOP_SCORES_FILE_PATH = "static/topscores";
const String GAME_OVER_FILE_PATH = "static/gameover";

const short PLATEAU_POS_Y = 4;         // definir l'emplacement du plateau
const short PLATEAU_POS_X = 0;         // definir l'emplacement du plateau
const short PLATEAU_NEXT_PIECE_X = 11; // definir l'emplacement de la nouveau piece
const short PLATEAU_NEXT_PIECE_Y = 0;  // definir l'emplacement de la nouveau piece
const short PLATEAU_SCORE_X = 88;      // definir l'emplacement du score
const short PLATEAU_SCORE_Y = 0;       // definir l'emplacement du score

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
    void setCoord(COORD);
    COORD getCoord();

    void move(short x, short y = 0);
    void exchangeWith(Shape *);

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

    void exchange(NodeSimple *, NodeSimple *);

    bool isLast(NodeSimple *);

    NodeSimple *getLast();

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
    ~ListDouble();

    bool isEmpty();
    bool isLast(NodeDouble *);

    void add(NodeSimple *, InsertionDirection = INSERT_RIGHT);
    void remove(NodeDouble *);

    void removeByNode(NodeSimple *);
    NodeDouble *findByNode(NodeSimple *);

    void setLast(NodeDouble *);
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
    bool gameOver;

    void removeNode(NodeSimple *);
    void checkConsecutive(bool (Game::*compFunc)(Shape *, Shape *));
    void removeConsecutives();
    void leftShift(ListDouble *list); // decalage a gauche

    bool compConsecutivesForms(Shape *, Shape *);
    bool compConsecutivesColors(Shape *, Shape *);

public:
    Game(); // initialisation du jeu
    ~Game();

    void start(); // lancer un nouveau jeu
    void reset();

    Shape *randShape();

    void updateNextShape();
    void updateScore(unsigned int increase);

    void insert(InsertionDirection = INSERT_RIGHT);

    void leftShiftForms(Form form);    // decalage a gauche
    void leftShiftColors(Color color); // decalage a gauche

    void displayMenu();
    void displayGameOver();
    void displayRules();
    void displayBestScores();

    bool bestScore();
};