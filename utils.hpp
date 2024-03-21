#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>


typedef std::string String;

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

enum InsertionDirection
{
    INSERT_RIGHT,
    INSERT_LEFT
};

int randNumber(int min, int max);
Color randColor();
Form randForm();
String convertFormToSymbole(Form form);
int convertToColorCode(Color color);

int abs(int num); // calcul la valeur absulue d'un nombre 