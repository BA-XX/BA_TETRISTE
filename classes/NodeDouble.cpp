#include "../game.hpp"

NodeDouble::NodeDouble(NodeSimple *node)
{
    this->node = node;
    prev = next = this; // NodeDouble point sur lui meme
}

NodeSimple *NodeDouble::getNode()
{
    return node;
}

void NodeDouble::exchangeWith(NodeDouble *node)
{
    if (prev == node)
        return;

    NodeDouble *tempNext = node->getNext();

    // Mettre à jour les liens du prédécesseur du nœud actuel

    prev->setNext(node);
    // Mettre à jour les liens du successeur du nœud passé

    tempNext->setPrev(this);

    // Mettre à jour les liens du nœud passé
    node->setNext(this);
    node->setPrev(prev);

    // Mettre à jour les liens du nœud actuel
    setNext(tempNext);
    setPrev(node);
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