#include "utils.hpp"

int randNumber(int min, int max)
{
    return min + std::rand() % (max - min + 1);
}

Color randColor()
{
    int rand = randNumber(1, 4); // nous avons 4 choix enum

    switch (rand)
    {
    case 1:
        return red;
        break;
    case 2:
        return blue;
        break;
    case 3:
        return yellow;
        break;
    case 4:
        return green;
        break;
    }
    return red;
}
Form randForm()
{
    int rand = randNumber(1, 4); // nous avons 4 choix enum

    switch (rand)
    {
    case 1:
        return square;
        break;
    case 2:
        return triangle;
        break;
    case 3:
        return circle;
        break;
    case 4:
        return diamond;
        break;
    }
    return square;
}

String convertFormToSymbole(Form form)
{

    switch (form)
    {
    case square:
        return "S";
        break;
    case triangle:
        return "T";
        break;
    case circle:
        return "C";
        break;
    case diamond:
        return "D";
        break;
    }

    return "S";
}

int convertToColorCode(Color color)
{

    switch (color)
    {
    case red:
        return FOREGROUND_RED;
        break;
    case blue:
        return FOREGROUND_BLUE;
        break;
    case yellow:
        return FOREGROUND_RED | FOREGROUND_GREEN;
        break;
    case green:
        return FOREGROUND_GREEN;
        break;
    }

    return FOREGROUND_RED;
}

void printWithColorAt(String text, int color, COORD coord)
{
    // Change la couleur du texte
    SetConsoleTextAttribute(hConsole, color);
    // Déplacer le curseur
    SetConsoleCursorPosition(hConsole, coord);

    std::cout << text;
    // Rétablit les attributs de couleur d'origine
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Function pour savaugarder un tableau d'entiers dans un fichier
void saveArray(const std::vector<int> &array, const std::string &fileName)
{
    std::ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        for (int i = 0; i < array.size(); ++i)
        {
            outputFile << array[i] << " ";
        }
        outputFile.close();
    }
}

// Function pour retirer un tableau d'entiers d'un fichier
std::vector<int> loadArray(const std::string &fileName)
{
    std::ifstream inputFile(fileName);
    std::vector<int> loadedArray;

    if (inputFile.is_open())
    {
        int value;
        while (inputFile >> value)
        {
            loadedArray.push_back(value);
        }
        inputFile.close();
    }
    else
    {
        // si le fichier n'exist pas
        saveArray(loadedArray, fileName); // creer un nouveau fichier
        loadArray(fileName);
    }

    return loadedArray;
}
