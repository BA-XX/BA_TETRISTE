#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

typedef std::string String;

enum Form
{
    square = 0,
    triangle = 1,
    circle = 2,
    diamond = 3
};

enum Color
{
    red = 0,
    blue = 1,
    yellow = 2,
    green = 3
};

enum InsertionDirection
{
    INSERT_RIGHT,
    INSERT_LEFT
};

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int randNumber(int min, int max);
Color randColor();
Form randForm();
String convertFormToSymbole(Form form);
int convertToColorCode(Color color);
void printWithColorAt(String text , int color , COORD coord);

int abs(int num); // calcul la valeur absulue d'un nombre