#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

typedef std::string String;

enum Form
{
    square = 'S',
    triangle = 'T',
    circle = 'C',
    diamond = 'D'
};

enum Color
{
    red = FOREGROUND_RED,
    blue = FOREGROUND_BLUE,
    yellow = FOREGROUND_RED | FOREGROUND_GREEN,
    green = FOREGROUND_GREEN
};

enum InsertionDirection
{
    INSERT_RIGHT,
    INSERT_LEFT
};

int randNumber(int min , int max);
Color randColor();
Form randForm();