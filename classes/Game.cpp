#include "../game.hpp"

void Game::removeNode(NodeDouble *node)
{
    /* TODO : Amélioration en termes de rapidité :
       Actuellement, chaque fois qu'il est nécessaire de trouver un nœud,
       il faut parcourir toute la liste.
       Cependant, on peut, par exemple, récupérer la liste concernée et la parcourir.
       Par exemple, si l'on trouve des pièces consécutives dans la liste des carrés,
       il faut la récupérer avec le type de la liste (formes), puis rechercher dans la liste des couleurs. */

    NodeSimple *temp = node->getNode();

    // supprimer le nœud de la liste des formes et des couleurs
    listForms[node->getNode()->getShape()->getForm()]->removeByNode(temp);
    listColors[node->getNode()->getShape()->getColor()]->removeByNode(temp);

    // supprimer le noeud du plateu
    plateau->remove(temp);
}
bool Game::isConsecutive(Shape *first, Shape *second)
{
    return (second->getCoord().X - first->getCoord().X) == 1;
}

void Game::checkConsecutive(ListDouble *list)
{
    if (list->getSize() < 3 || list->isEmpty())
        return;

    NodeDouble *temp = list->getLast()->getNext();

    int numConsective = 1;

    while (temp != list->getLast() && !list->isEmpty())
    {
        if (isConsecutive(temp->getNode()->getShape(), temp->getNext()->getNode()->getShape()))
            numConsective++;
        else
            numConsective = 1;

        if (numConsective == 3)
        {

            removeNode(temp->getNext());
            removeNode(temp->getPrev());
            removeNode(temp);

            updateScore(30); // augmenter le score de 30

            numConsective = 1; // reintialiser le conteur des forms consectives

            if (list->isEmpty())
                break;
        }

        temp = temp->getNext();
    }
}

Game::Game()
{

    score = 0;

    for (int i = 0; i < 4; i++)
    { // allocation de memoire
        listForms[i] = new ListDouble();
        listColors[i] = new ListDouble();
    }

    // réinitialiser le generateur de nombre aléatoire
    std::srand(std::time(nullptr));

    // initialiser le prochain
    std::cout << "Prochain :";
    this->updateNextShape();

    updateScore(0); // afficher score

    // initialiser le plateau
    plateau = new ListSimple();

    std::cout << "\n\n\nPlateau : ";
    plateau->display();
}
Game::~Game()
{
    delete plateau;

    for (int i = 0; i < 4; i++)
    { // liberation de la memoire
        delete listForms[i];
        delete listColors[i];
    }
}
Shape *Game::randShape()
{
    return new Shape(randForm(), randColor());
}

void Game::start()
{
    system("cls");
}

void Game::updateNextShape()
{
    nextShape = randShape();
    nextShape->setCoord(11, 0);
    nextShape->display();
}

void Game::updateScore(unsigned int increase)
{

    SetConsoleCursorPosition(hConsole, {40, 0});
    std::cout << "Score : " << (score += increase);
}

void Game::insert(InsertionDirection dir)
{

    NodeSimple *temp = new NodeSimple(nextShape);

    listForms[nextShape->getForm()]->add(temp, dir);
    listColors[nextShape->getColor()]->add(temp, dir);

    plateau->add(temp, dir);
    plateau->display();

    checkConsecutive(listForms[nextShape->getForm()]);   // les pièces ont les mêmes formes
    checkConsecutive(listColors[nextShape->getColor()]); // les pièces ont les mêmes couleurs

    // vérifier si la taille du plateau est égale au maximum afin que le jeu d'affichage soit terminé
    if (plateau->getSize() == MAX_PLATEAU_SIZE)
    {
        this->displayGameOver();
        return;
    }

    updateNextShape();
}

void Game::displayGameOver()
{

    system("cls");

    std::cout << R"(
   _____                         ____                   _ 
  / ____|                       / __ \                 | |
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __  | |
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__| | |
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |    |_|
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|    (_)
                                                                                                           
    )" << std::endl;
}
