#include "../game.hpp"

ListSimple::ListSimple()
{
    last = NULL;
    size = 0;
}

ListSimple::~ListSimple()
{
    NodeSimple *temp = last;

    while ((temp = temp->getNext()) != last)
    {
        delete temp;
    }

    delete last;
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
        prev->setNext(node->getNext()); // changer le suivante du precedent

        delete last; // liberer l'espace de dernier element

        last = prev; // changer la valeur du last
        size--;      // diminuer

        return;
    }

    NodeSimple *temp = node->getNext();

    do
    {
        temp->getShape()->move(temp->getShape()->getCoord().X - 1, PLATEAU_POS_Y);
        temp = temp->getNext();

    } while (temp != last->getNext());

    prev->setNext(node->getNext()); // changer le suivante du precedent
    delete node;                    // liberer la memoire
    size--;
}

bool ListSimple::isLast(NodeSimple *node)
{
    return last == node;
}

NodeSimple *ListSimple::findPrev(NodeSimple *node)
{
    if (isEmpty())
        return NULL;

    NodeSimple *prev = last->getNext(); // commencer depuis le premier element

    while (prev->getNext() != node)
        prev = prev->getNext();

    return prev;
}
size_t ListSimple::getSize()
{
    return size;
}