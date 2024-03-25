#include "../game.hpp"

void Game::removeNode(NodeSimple *node)
{
    // supprimer le nœud de la liste des formes et des couleurs
    listForms[node->getShape()->getForm()]->removeByNode(node);
    listColors[node->getShape()->getColor()]->removeByNode(node);

    // supprimer le noeud du plateu
    plateau->remove(node);
}
bool Game::isConsecutive(Shape *first, Shape *second)
{
    return (abs(second->getCoord().X - first->getCoord().X)) == 1;
}

void Game::checkConsecutive()
{

    NodeSimple *temp = plateau->getLast()->getNext(); // first element

    int numConsecutiveFroms = 1;
    int numConsecutiveColors = 1;

    while (temp != plateau->getLast() && !plateau->isEmpty())
    {
        if (temp->getShape()->getForm() == temp->getNext()->getShape()->getForm())
            numConsecutiveFroms++;
        else
            numConsecutiveFroms = 1;

        if (temp->getShape()->getColor() == temp->getNext()->getShape()->getColor())
            numConsecutiveColors++;
        else
            numConsecutiveColors = 1;

        if (numConsecutiveFroms == 3 || numConsecutiveColors == 3)
        {

            removeNode(temp->getNext());
            removeNode(plateau->findPrev(temp));
            removeNode(temp);

            updateScore(30); // augmenter le score de 30

            numConsecutiveFroms = numConsecutiveColors = 1; // reintialiser les conteurs

            if (plateau->isEmpty())
                break;
        }

        temp = temp->getNext();
    }
}

void Game::leftShift(ListDouble *list)
{

    if (list->isEmpty() || list->getSize() == 1)
        return;

    NodeDouble *newLast = list->getLast()->getNext(); // premier de la list
    NodeDouble *temp = newLast->getNext(); 

    while (temp->getNext() !=  newLast->getNext())
    {
        plateau->exchange(newLast->getNode(), temp->getNode());
        temp = temp->getNext();
    }

    list->setLast(newLast);
}

Game::Game()
{
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

    checkConsecutive(); // vérifier les pièces consécutives

    // vérifier si la taille du plateau est égale au maximum afin que le jeu d'affichage soit terminé
    if (plateau->getSize() == MAX_PLATEAU_SIZE)
    {
        this->displayGameOver();
        return;
    }

    updateNextShape();
}

void Game::leftShiftForms(Form form)
{
    leftShift(listForms[form]);
}
void Game::leftShiftColors(Color color)
{
    leftShift(listColors[color]);
}

void Game::displayMenu()
{
    system("cls");

    short choix;

    std::cout << R"( 
  ____    _      _____ _____ _____ ____  ___ ____ _____ _____ 
 | __ )  / \    |_   _| ____|_   _|  _ \|_ _/ ___|_   _| ____|
 |  _ \ / _ \     | | |  _|   | | | |_) || |\___ \ | | |  _|  
 | |_) / ___ \    | | | |___  | | |  _ < | | ___) || | | |___ 
 |____/_/   \_\___|_| |_____| |_| |_| \_\___|____/ |_| |_____| v1.0
             |_____|                                           @BA_XX                      
                                                                        
)" << std::endl;

    std::cout << "1. Nouveau Jeu " << std::endl;
    std::cout << "0. Quitter";
    std::cout << "\n\nQuel est votre choix ? :";
    std::cin >> choix;

    switch (choix)
    {
    case 1:
        start();
        break;
    case 0:
        exit(0);
        break;
    }
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
