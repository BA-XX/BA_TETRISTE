#include "../game.hpp"

void Game::removeNode(NodeSimple *node)
{

    // supprimer le nœud de la liste des formes et des couleurs
    listForms[node->getShape()->getForm()]->removeByNode(node);
    listColors[node->getShape()->getColor()]->removeByNode(node);

    // supprimer le noeud du plateu
    plateau->remove(node);
}

void Game::checkConsecutive(bool (Game::*compFunc)(Shape *first, Shape *second))
{
    if (plateau->getSize() < MAX_CONSECUTVIES_PIECES || plateau->isEmpty())
        return;

    NodeSimple *first, *temp;
    first = temp = plateau->getLast()->getNext(); // first element

    int numConsecutive = 1;

    while (temp != plateau->getLast() && !plateau->isEmpty())
    {
        if ((this->*compFunc)(temp->getShape(), temp->getNext()->getShape()))
            numConsecutive++;
        else
        {
            numConsecutive = 1;
            first = temp->getNext();
        }

        if (numConsecutive >= MAX_CONSECUTVIES_PIECES)
        {
            NodeSimple *temp2 = first;

            for (int i = 0; i < numConsecutive; i++)
            {
                removeNode(temp2);

                temp2 = temp2->getNext();
            }

            updateScore(numConsecutive * SCORE_REWARD_COEFFICIENT); // augmenter le score de 30

            numConsecutive = 1; // reintialiser les conteurs

            if (plateau->isEmpty()) // quiter la boucle si le plateau est vide
            {
                updateScore(100); // Bonus si le plateau est videe
                break;
            }
            else
            {
                // reintialiser la boucle pour commencer du nouveau premier
                first = temp = plateau->getLast()->getNext();
                continue;
            }
        }

        temp = temp->getNext();
    }
}

void Game::removeConsecutives()
{
    checkConsecutive(compConsecutivesForms);
    checkConsecutive(compConsecutivesColors);
}
void Game::leftShift(ListDouble *list)
{
    if (list->isEmpty() || list->getSize() == 1)
        return;

    NodeDouble *newLast = list->getLast()->getNext(); // premier de la list
    NodeDouble *temp = newLast->getNext();

    while (temp != newLast)
    {
        plateau->exchange(newLast->getNode(), temp->getNode());
        temp = temp->getNext();
    }

    list->setLast(newLast);
}

bool Game::compConsecutivesForms(Shape *first, Shape *second)
{
    return first->getForm() == second->getForm();
}
bool Game::compConsecutivesColors(Shape *first, Shape *second)
{
    return first->getColor() == second->getColor();
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
    gameOver = false;

    for (int i = 0; i < 4; i++)
    { // allocation de memoire
        listForms[i] = new ListDouble();
        listColors[i] = new ListDouble();
    }

    // reinitialiser le generateur de nombre aleatoire
    std::srand(std::time(nullptr));

    // initialiser le prochain
    std::cout << "Prochain :";

    updateNextShape(); // gener une nouvelle piece
    updateScore(0);    // afficher score

    // initialiser le plateau
    plateau = new ListSimple();

    std::cout << "\n\n\nPlateau : ";
    plateau->display();

    displayControlsMenu();

    while (!gameOver)
    {
        switch (getch())
        {
        case 108: // l
            insert(INSERT_LEFT);
            break;
        case 114:     // r
            insert(); // par default INSERT_RIGHT
            break;

            /*Left shift by forms*/

        case 115: // s
            leftShiftForms(square);
            break;
        case 116: // t
            leftShiftForms(triangle);
            break;
        case 99: // c
            leftShiftForms(circle);
            break;
        case 100: // d
            leftShiftForms(diamond);
            break;

            /*Left shift by colors*/
        case 82: // R
            leftShiftColors(red);
            break;
        case 66: // B
            leftShiftColors(blue);
            break;
        case 89: // Y
            leftShiftColors(yellow);
            break;
        case 71: // G
            leftShiftColors(green);
            break;
        }
    }
}

void Game::reset()
{
    score = 0;

    for (int i = 0; i < 4; i++)
    { // liberation de la memoire
        delete listForms[i];
        delete listColors[i];
    }

    // reinitialiser le generateur de nombre aleatoire
    std::srand(std::time(nullptr));

    // supprimer le plateau
    delete plateau;
}
void Game::updateNextShape()
{
    nextShape = randShape();
    nextShape->setCoord(11, 0);
    nextShape->display();
}

void Game::updateScore(unsigned int increase)
{

    SetConsoleCursorPosition(hConsole, {80, 0});
    std::cout << "Score : " << (score += increase);
}

void Game::insert(InsertionDirection dir)
{

    NodeSimple *temp = new NodeSimple(nextShape);

    listForms[nextShape->getForm()]->add(temp, dir);
    listColors[nextShape->getColor()]->add(temp, dir);

    plateau->add(temp, dir);
    plateau->display();

    removeConsecutives(); // verifier les pieces consecutives

    // verifier si la taille du plateau est egale au maximum afin que le jeu d'affichage soit termine
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
    removeConsecutives();
}
void Game::leftShiftColors(Color color)
{
    leftShift(listColors[color]);
    removeConsecutives();
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

    std::cout << "  1. Nouveau Jeu " << std::endl;
    std::cout << "  2. Meilleurs scores " << std::endl;
    std::cout << "  3. Les regles  " << std::endl;
    std::cout << "  0. Quitter";
    std::cout << "\n\n  Quel est votre choix ? :";
    std::cin >> choix;

    switch (choix)
    {
    case 1:
        start();
        break;
    case 3:
        displayRules();
        break;
    case 0:
        exit(0);
        break;
    }
}
void Game::displayGameOver()
{
    gameOver = true;

    system("cls");
    short choix;

    std::cout << R"(
   _____                         ____                   _ 
  / ____|                       / __ \                 | |
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __  | |
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__| | |
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |    |_|
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|    (_)
                                                                                       
    )" << std::endl;

    if (bestScore())
        std::cout << "           Bravo ! Nouveau meilleur score" << std::endl;

    std::cout << "                      Score: " << score << std::endl;
    std::cout << "\n\n\n## cliquez sur n'importe quelle touche pour revenir au menu ##" << std::endl;
    getch();
    reset();
    displayMenu();
}

void Game::displayControlsMenu()
{
    SetConsoleCursorPosition(hConsole, {0, 12});
    std::cout << "----------------------------------------- Controles ---------------------------------------------" << std::endl;
    std::cout << "- l : Ajouter a gauche.          - r : Ajouter a droite.            - s : Decalage des carres " << std::endl;
    std::cout << "- t : Decalage des triangles.    - c : Decalage des cercles.        - d : Decalage des losanges " << std::endl;
    std::cout << "- R : Decalage des rouges.       - B : Decalage des blues.          - Y : Decalage des jaunes. " << std::endl;
    std::cout << "- G : Decalage des vertes." << std::endl;
}

void Game::displayRules()
{
    system("cls");

    std::cout << R"(
______ _   _ _      _____ _____ 
| ___ \ | | | |    |  ___/  ___|
| |_/ / | | | |    | |__ \ `--. 
|    /| | | | |    |  __| `--. \
| |\ \| |_| | |____| |___/\__/ /
\_| \_|\___/\_____/\____/\____/ 
                                
# But du jeu : 
Le joueur doit former des ensembles de trois pieces consecutives ayant la meme couleur ou forme 
pour les faire disparaitre et gagner des points.

# Deroulement du jeu :
1. Le jeu commence avec un plateau vide.
2. A chaque tour, une nouvelle piece est generee aleatoirement.
3. Le joueur choisit ou placer la nouvelle piece sur le plateau.
4. Si le joueur reussit a former un groupe de trois pieces consecutives ayant la meme couleur ou 
   forme, ces trois pieces sont retirees du plateau, et le joueur recoit 10 points pour chaque 
   piece ainsi retiree.
5. Si le plateau est vide, le joueur recoit un bonus de 100 points.
6. Le jeu se poursuit jusqu'a ce que le plateau contienne 15 pieces.

# Conditions de fin du jeu : 
Le jeu se termine lorsque le plateau contient 15 pieces. Le score total du joueur est calcule 
en ajoutant les points obtenus pour chaque piece retiree et les bonus de 100 points chaque fois 
que le plateau est vide.

# Objectif : 
Atteindre le meilleur score en planifiant strategiquement l'insertion ou le decalage des pieces.

                                )"
              << std::endl;

    std::cout << "# Controles :" << std::endl;
    std::cout << "- l : Ajouter a gauche." << std::endl;
    std::cout << "- r : Ajouter a droite." << std::endl;
    std::cout << "- s : Decalage des carres." << std::endl;
    std::cout << "- t : Decalage des triangles." << std::endl;
    std::cout << "- c : Decalage des cercles." << std::endl;
    std::cout << "- d : Decalage des losanges." << std::endl;
    std::cout << "- R : Decalage des pieces rouges." << std::endl;
    std::cout << "- B : Decalage des pieces bleues." << std::endl;
    std::cout << "- Y : Decalage des pieces jaunes." << std::endl;
    std::cout << "- G : Decalage des pieces vertes." << std::endl
              << std::endl;

    std::cout << "\n\n\n## cliquez sur n'importe quelle touche pour revenir au menu ##" << std::endl;
    SetConsoleCursorPosition(hConsole, {0, 0});

    getch();
    displayMenu();
}

bool Game::bestScore()
{
    if (score == 0)
        return false;

    std::vector<int> scores = loadArray(SCORE_FILE_NAME);

    if (scores.size() <= 10)
    {
        scores[scores.size()] = score;
        saveArray(scores, SCORE_FILE_NAME); // savaugarder les nouveaux scores

        return true;
    }

    for (int i = 0; i < scores.size(); ++i)
    {
        if (scores[i] < score)
        {
            for (int j = i; j < (scores.size() - 1); j++)
                scores[j + 1] = scores[j];
            scores[i] = score;

            saveArray(scores, SCORE_FILE_NAME); // savaugarder les nouveaux scores

            return true;
        }
    }

    return false;
}
