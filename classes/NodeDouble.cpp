#include "../headers/game.hpp"

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