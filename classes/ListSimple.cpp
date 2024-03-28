#include "../headers/game.hpp"

ListSimple::ListSimple()
{
    last = NULL;
    size = 0;
}

ListSimple::~ListSimple()
{
    if (!isEmpty())
    {
        NodeSimple *temp = last->getNext();

        while (!isLast(temp))
        {
            NodeSimple *next = temp->getNext();
            delete temp;
            temp = next;
        }

        delete last;
    }
}
bool ListSimple::isEmpty()
{
    return last == NULL;
}

void ListSimple::display()
{
    if (isEmpty())
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
        node->getShape()->setCoord(PLATEAU_POS_X, PLATEAU_POS_Y); // position initiale
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
        node->getShape()->setCoord(PLATEAU_POS_X, PLATEAU_POS_Y);

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

    if (isEmpty())
        return;

    node->getShape()->remove(); // retirer le point de la console

    if (size == 1)
    {
        delete last;
        last = NULL;
        size = 0;
        return;
    }

    NodeSimple *prev = findPrev(node); // trouver l'element precedent

    if (isLast(node)) // s'il est le dernier
    {
        prev->setNext(last->getNext()); // changer le suivante

        delete last; // liberer l'espace de dernier element

        last = prev; // changer la valeur du last
        size--;      // diminuer

        return;
    }

    NodeSimple *temp = node->getNext();

    while (!isLast(temp))
    {
        temp->getShape()->move(temp->getShape()->getCoord().X - 1, PLATEAU_POS_Y);
        temp = temp->getNext();
    }

    // pour le dernier element
    last->getShape()->move(temp->getShape()->getCoord().X - 1, PLATEAU_POS_Y);

    prev->setNext(node->getNext()); // changer le suivante du precedent
    size--;

    delete node; // liberer la memoire
}

void ListSimple::exchange(NodeSimple *node1, NodeSimple *node2) // echanger deux piece du plateau
{
    if (node1 == node2 || size == 1 || isEmpty())
        return;

    NodeSimple *prev1 = findPrev(node1);
    NodeSimple *prev2 = findPrev(node2);

    NodeSimple *next1 = node1->getNext();
    NodeSimple *next2 = node2->getNext();

    if (next1 != node2 && next2 != node1) // si les pieces ne sont pas consecutives
    {
        node1->setNext(next2);
        node2->setNext(next1);

        prev1->setNext(node2);
        prev2->setNext(node1);
    }
    else if (next1 == node2 && next2 != node1) // si le suivant du node1 est le node2
    {
        node2->setNext(node1);
        node1->setNext(next2);

        prev1->setNext(node2);
    }
    else if (next2 == node1 && next1 != node2)  // si le suivant du node2 est le node1
    {
        node1->setNext(node2);
        node2->setNext(next1);

        prev2->setNext(node1);
    }

    if (isLast(node1)) // si le node1 est le dernier
        last = node2;

    if (isLast(node2)) // si le node2 est le dernier
        last = node1;

    node1->getShape()->exchangeWith(node2->getShape()); // echange des coordonnes des deux pieces
}

bool ListSimple::isLast(NodeSimple *node)
{
    return last == node;
}

NodeSimple *ListSimple::getLast()
{
    return last;
}
NodeSimple *ListSimple::findPrev(NodeSimple *node)
{
    if (isEmpty())
        return NULL;

    if (last->getNext() == node) // premier element
        return last;

    NodeSimple *temp = last->getNext();

    while (temp != last) // parcourir tout la list sauf le dernier element
    {
        if (temp->getNext() == node)
            return temp;

        temp = temp->getNext();
    }

    return NULL;
}
size_t ListSimple::getSize()
{
    return size;
}