#ifndef BOARD_H
#define BOARD_H



class Board {
public:

    Board(int size, bool diagonalWin);
    ~Board();

    bool placeMove(int row, int col, char symbol);
    bool checkWin(int row, int col, char symbol) const;
    bool isFull() const;
    void draw() const;
    bool getDiagonalWin() const;


    int getSize() const;
    char getCell(int row, int col) const;
    void setCell(int row, int col, char ch);



private:
    int size;
    char** cells;
    bool diagonalWin;

};





#endif // BOARD_H











