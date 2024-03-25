#include "../game.hpp"

ListDouble::ListDouble()
{
    last = NULL;
    size = 0;
}
bool ListDouble::isEmpty()
{
    return last == NULL;
}
bool ListDouble::isLast(NodeDouble *node)
{
    return last == node;
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
    temp->setNext(last->getNext()); // remplacer le suivant par celui du dernier
    temp->setPrev(last);
    last->getNext()->setPrev(temp);
    last->setNext(temp);

    if (dir == INSERT_RIGHT)
    {
        last = temp;
    }

    size++;
}

void ListDouble::remove(NodeDouble *node)
{
    if (size == 1)
    {
        delete node;
        last = NULL;
        size = 0;
        return;
    }

    NodeDouble *prev = node->getPrev();
    NodeDouble *next = node->getNext();

    prev->setNext(next);
    next->setPrev(prev);

    if (isLast(node))
    {
        last = prev;
    }

    delete node;
    size--;
}

void ListDouble::removeByNode(NodeSimple *node)
{
    NodeDouble *temp = findByNode(node);

    if (temp != NULL)
        remove(temp);
}
NodeDouble *ListDouble::findByNode(NodeSimple *node)
{
    NodeDouble *temp = last;

    do
    {
        if (temp->getNode() == node)
            return temp;

    } while ((temp = temp->getNext()) != last);

    return NULL;
}

void ListDouble::setLast(NodeDouble *node)
{
    last = node;
}
NodeDouble *ListDouble::getLast()
{
    return last;
}

size_t ListDouble::getSize()
{
    return size;
}
