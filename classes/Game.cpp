#include "../headers/game.hpp"

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
                NodeSimple *next = temp2->getNext(); // stocker la valeur du suivant

                removeNode(temp2); // supprimer le node actuel

                temp2 = next; // changer la valeur de temp2 par le suivant
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
    plateau = NULL;
    score = 0;
    gameOver = true;
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

    std::cout << readFileToString(PLATEAU_FILE_PATH);
    // reinitialiser le generateur de nombre aleatoire
    std::srand(std::time(nullptr));

    // initialiser le prochain
    updateNextShape(); // gener une nouvelle piece
    updateScore(0);    // afficher score

    // initialiser le plateau
    plateau = new ListSimple();

    plateau->display();

    while (!gameOver)
    {
        switch (getch())
        {
        case 75: // left arrow key
            insert(INSERT_LEFT);
            break;
        case 77:      // right arrow key
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

        case 48: // 0

            reset();
            displayMenu();
            break;
        }
    }
}

void Game::reset()
{
    score = 0;
    gameOver = true;

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
    nextShape->setCoord(PLATEAU_NEXT_PIECE_X, PLATEAU_NEXT_PIECE_Y);
    nextShape->display();
}

void Game::updateScore(unsigned int increase)
{

    SetConsoleCursorPosition(hConsole, {PLATEAU_SCORE_X, PLATEAU_SCORE_Y});
    std::cout << (score += increase);
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

    std::cout << readFileToString(MENU_FILE_PATH);

    while (true)
    {
        switch (getch())
        {
        case 49: // 1
            start();
            break;
        case 50: // 2
            displayBestScores();
            break;
        case 51: // 3
            displayRules();
            break;
        case 48: // 0
            exit(0);
            break;
        default:
            continue;
        }

        break;
    }
}
void Game::displayGameOver()
{
    gameOver = true;

    system("cls");
    short choix;

    std::cout << readFileToString(GAME_OVER_FILE_PATH);

    if (bestScore())
        std::cout << "           Bravo ! Nouveau Meilleur Score" << std::endl;

    std::cout << "                      Score: " << score << std::endl
              << std::endl;

    std::cout << "                ->  Relancer (ESPACE)  <-" << std::endl;
    std::cout << "\n\n\n## cliquez sur n'importe quelle touche pour revenir au menu ##" << std::endl;
    switch (getch())
    {
    case 32: // espace
        reset();
        start();
        break;
    default:
        reset();
        displayMenu();
        break;
    }
}

void Game::displayRules()
{
    system("cls");

    std::cout << readFileToString(RULES_FILE_PATH);

    std::cout << "\n\n\n## cliquez sur n'importe quelle touche pour revenir au menu ##" << std::endl;
    SetConsoleCursorPosition(hConsole, {0, 0});

    getch();
    displayMenu();
}

void Game::displayBestScores()
{
    system("cls");

    std::cout << readFileToString(TOP_SCORES_FILE_PATH);

    std::vector<int> scores = sort(loadArray(SCORE_FILE_PATH));

    for (size_t i = 0; i < scores.size(); i++)
        std::cout << "  " << i + 1 << "- " << scores[i] << std::endl;

    std::cout << "\n\n\n## cliquez sur n'importe quelle touche pour revenir au menu ##" << std::endl;
    SetConsoleCursorPosition(hConsole, {0, 0});

    getch();
    displayMenu();
}

bool Game::bestScore()
{
    if (score == 0)
        return false;

    std::vector<int> scores = loadArray(SCORE_FILE_PATH);

    size_t numScores = scores.size();

    int bestScore = (numScores > 0) ? scores[0] : 0;

    if (numScores < 10)
    {
        scores.push_back(score);

        scores = sort(scores);              // trie le tableau
        saveArray(scores, SCORE_FILE_PATH); // savaugarder les nouveaux scores

        return bestScore < score; // comparer le premier score avec l'actuel score
    }

    for (int i = 0; i < numScores; ++i)
    {
        if (scores[i] < score)
        {
            scores.push_back(score);

            scores = sort(scores); // trie le tableau

            if (scores.size() > 10)
                scores.pop_back();

            saveArray(scores, SCORE_FILE_PATH); // savaugarder les nouveaux scores

            return bestScore < score;
        }
    }

    return false;
}
