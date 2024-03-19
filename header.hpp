#pragma once

enum Form
{
    square,
    triangle,
    circle,
    diamond
};

enum Color
{
    red,
    blue,
    yellow,
    green
};

class Shape
{
private:
    Form form;
    Color color;

public:
    Shape(Form, Color);
};

Shape::Shape(Form form, Color color)
{
    this->form = form;
    this->color = color;
}

class NodeDouble
{
private:
public:
    NodeDouble();
    ~NodeDouble();
};

NodeDouble::NodeDouble(/* args */)
{
}

NodeDouble::~NodeDouble()
{
}
