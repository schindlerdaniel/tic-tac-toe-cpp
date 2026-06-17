#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Figure.h"



class Game {
public:

    Game();
    ~Game();

    void run();
    bool saveGame(const char* filename);
    bool loadGame(const char* filename);

private:

    Board* board;
    Figure* currentPlayer;
    XFigure playerX;
    OFigure playerO;
    bool gameOver;

    bool handleMove();
    void switchPlayer();
    bool askNewGame() const;
    void newGame();

};





#endif // GAME_H









