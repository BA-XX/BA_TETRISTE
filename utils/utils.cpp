#include "../headers/utils.hpp"

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

// Fonction pour sauvegarder un tableau d'entiers dans un fichier binaire
void saveArray(const std::vector<int> &array, const std::string &fileName)
{
    std::ofstream outputFile(fileName, std::ios::binary);
    if (outputFile.is_open())
    {
        size_t size = array.size();
        // Écriture de la taille du tableau
        outputFile.write(reinterpret_cast<const char *>(&size), sizeof(size));
        // Écriture des données du tableau
        outputFile.write(reinterpret_cast<const char *>(array.data()), size * sizeof(int));
        outputFile.close();
    }
}

// Fonction pour charger un tableau d'entiers depuis un fichier binaire
std::vector<int> loadArray(const std::string &fileName)
{
    std::ifstream inputFile(fileName, std::ios::binary);
    std::vector<int> loadedArray;

    if (inputFile.is_open())
    {
        size_t size;
        // Lecture de la taille du tableau
        inputFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        loadedArray.resize(size);
        // Lecture des données du tableau
        inputFile.read(reinterpret_cast<char *>(loadedArray.data()), size * sizeof(int));
        inputFile.close();
    }

    return loadedArray;
}

std::vector<int> sort(const std::vector<int> &array)
{
    if (array.size() < 2)
        return array;

    // Créer une copie du vecteur d'entrée
    std::vector<int> temp = array;

    // Effectuer le tri par insertion
    for (size_t i = 1; i < temp.size(); ++i)
    {
        int key = temp[i];
        int j = i - 1;
        // Déplacer les éléments de temp[0..i-1] qui sont plus grands que la clé vers une position avant leur position actuelle
        while (j >= 0 && temp[j] < key)
        {
            temp[j + 1] = temp[j];
            --j;
        }
        temp[j + 1] = key;
    }

    // Retourner le vecteur trié
    return temp;
}

String readFileToString(const String &filename)
{

    std::ifstream file(filename); // Ouvrir le fichier en mode lecture
    String content;               // Chaîne de caractères pour stocker le contenu du fichier

    if (file.is_open())
    {
        // Lire le contenu du fichier ligne par ligne
        String line;
        while (std::getline(file, line))
        {
            content += line + "\n"; // Ajouter chaque ligne à la chaîne de caractères avec un retour à la ligne
        }

        file.close(); // Fermer le fichier
    }
    else
        std::cout << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;

    return content;
}
