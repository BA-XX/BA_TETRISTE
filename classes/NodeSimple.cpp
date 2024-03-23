#include "../game.hpp"

NodeSimple::NodeSimple(Shape *shape)
{
    this->shape = shape;
    this->next = this;
}
NodeSimple::~NodeSimple()
{
    delete shape;
}
Shape *NodeSimple::getShape()
{
    return shape;
}
void NodeSimple::setNext(NodeSimple *next)
{
    this->next = next;
}
NodeSimple *NodeSimple::getNext()
{
    return next;
}