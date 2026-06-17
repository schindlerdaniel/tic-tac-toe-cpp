#include "Game.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>



Game::Game() : board(nullptr), currentPlayer(nullptr), gameOver(false) {}


Game::~Game() {
    delete board;
}



void Game::newGame() {

    int size;
    char diagChar;
    std::cout << "Adja meg a tabla meretet (3-20): ";
    std::cin >> size;
    while (size < 3 || size > 20) {
        std::cerr << "Hibas meret! 3 es 20 kozott kell lennie." << std::endl;
        std::cin >> size;

    }

    std::cout << "Atlokkal lehet nyerni? (i/n): ";
    std::cin >> diagChar;
    bool diag = (diagChar == 'i' || diagChar == 'I');


    delete board;
    board = new Board(size, diag);
    currentPlayer = &playerX;
    gameOver = false;


}

bool Game::askNewGame() const {

    char ch;
    std::cout << "Szeretne uj jatekot kezdeni? (i/n): ";
    std::cin >> ch;
    while (ch != 'i' && ch != 'I' && ch != 'n' && ch != 'N') {
        std::cerr << "Ervenytelen valasz! (i/n)" << std::endl;
        std::cin >> ch;

    }

    return (ch == 'i' || ch == 'I');


}

void Game::run() {

    char loadChar;
    std::cout << "Mentes betoltese? (i/n): ";
    std::cin >> loadChar;
    if ((loadChar== 'i' || loadChar == 'I') &&  loadGame("save.dat")) {
        std::cout << "Mentes betoltve." << std::endl;
    }
    else {
        newGame();

    }

    bool playAgain = true;

    while (playAgain) {
        board->draw();
        while (!gameOver) {
            if( handleMove()) {
                board->draw();
                break;

            }

            board->draw();
            std::cout << (currentPlayer->getSymbol()) << " kovetkezik:" << std::endl;

        }

        playAgain = askNewGame();
        if (playAgain) {
            newGame();
        }

    }


}


bool Game::handleMove() {

    char input[100];
    std::cin >> input;
    if (strcmp(input, "mentes") == 0) {
        if (saveGame("save.dat"))
            std::cout << "Jatek elmentve." << std::endl;
        else
            std::cerr << "Mentes sikertelen!" << std::endl;
        return false;
    }

    if (!std::isalpha(static_cast<unsigned char>(input[0]))) {
        std::cerr << "Ervenytelen lepes! Probald ujra." << std::endl;
        return false;

    }
    bool allDigits = true;
    for (int i = 1; input[i] != '\0'; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) {
            allDigits = false;
            break;

        }

    }

    if (!allDigits || input[1] == '\0') {
        std::cerr << "Ervenytelen lepes! Probald ujra." << std::endl;
        return false;

    }


    int col = std::toupper(static_cast<unsigned char>(input[0])) - 'A';
    int row = atoi(input + 1) - 1;
    int size = board->getSize();
    if (col < 0 || col >= size || row < 0 || row >= size) {
        std::cerr << "Ervenytelen lepes! Probald ujra." << std::endl;
        return false;
    }

    if (board->getCell(row, col) != '.') {
        std::cerr << "A mezo mar foglalt." << std::endl;
        return false;
    }

    char symbol = currentPlayer->getSymbol();
    board->placeMove(row, col, symbol);

    if (board->checkWin(row, col, symbol)) {
        std::cout << symbol << " nyert!" << std::endl;
        gameOver = true;
        return true;
    }


    if (board->isFull()) {
        std::cout << "Dontetlen!" << std::endl;
        gameOver = true;
        return true;
    }

    switchPlayer();
    return false;
}



void Game::switchPlayer() {
    if (currentPlayer == &playerX)
        currentPlayer = &playerO;
    else
        currentPlayer = &playerX;
}



bool Game::saveGame(const char* filename) {
    std::ofstream out(filename);
    if (!out) return false;

    int size = board->getSize();
    out << size << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            out << board->getCell(i, j);
        out << std::endl;
    }

    out << currentPlayer->getSymbol() << std::endl;
    out << (board->getDiagonalWin() ? 1 : 0) << std::endl;

    out.close();

    return true;
}



bool Game::loadGame(const char* filename) {
    std::ifstream in(filename);
    if (!in) return false;

    int size;
    in >> size;
    if (size < 3 || size > 20) return false;

    Board* temp = new Board(size, false);
    for (int i = 0; i < size; ++i) {
        char line[100];
        in >> line;
        for (int j = 0; j < size; ++j) {
            temp->setCell(i, j, line[j]);
        }
    }

    char nextPlayer;
    int diagInt;
    in >> nextPlayer;
    in >> diagInt;
    in.close();

    if (diagInt != (temp->getDiagonalWin() ? 1 : 0)) {
        Board* corrected = new Board(size, diagInt == 1);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                corrected->setCell(i, j, temp->getCell(i, j));
        delete temp;
        temp = corrected;
    }

    delete board;
    board = temp;
    currentPlayer = (nextPlayer == 'X') ? (Figure*)&playerX : (Figure*)&playerO;    return true;
}
