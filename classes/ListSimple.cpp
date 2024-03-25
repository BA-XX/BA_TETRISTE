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

void ListSimple::exchange(NodeSimple *node1, NodeSimple *node2)
{
    if (node1 == node2 || size == 1 || isEmpty())
        return;

    NodeSimple *tempPrev1 = findPrev(node1);
    NodeSimple *tempPrev2 = findPrev(node2);

    NodeSimple *tempNext = node1->getNext();

    tempPrev1->setNext(node2);
    tempPrev2->setNext(node1);

    node1->setNext(node2->getNext());
    node2->setNext(tempNext);

    if (isLast(node1))
        last = node2;

    if (isLast(node2))
        last = node1;

    node1->getShape()->exchangeWith(node2->getShape());
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

    NodeSimple *prev = last->getNext(); // commencer depuis le premier element

    while (prev->getNext() != node)
        prev = prev->getNext();

    return prev;
}
size_t ListSimple::getSize()
{
    return size;
}