#include "Board.h"
#include <iostream>



Board::Board(int size, bool diagonalWin) : size(size), diagonalWin(diagonalWin) {
    cells = new char *[size];
    for (int i = 0; i < size; ++i) {
        cells[i] = new char [size];
        for (int j=0; j < size; ++j) {
            cells[i][j] = '.';

        }
    }

}



Board::~Board() {
    for (int i=0; i < size; ++i)  {
        delete[] cells[i];
    }

    delete[] cells;

}



bool Board::placeMove(int row, int col, char symbol) {
    if (row < 0 || row >=size || col < 0 || col >= size)
        return false;

    if (cells[row][col] != '.')
        return false;

    cells[row][col] = symbol;

    return true;

}



bool Board::checkWin(int row, int col, char symbol) const {

    const int WIN_COUNT = 3;
    int count;

    count = 1;
    for (int c = col - 1; c >= 0 && cells[row][c] == symbol; --c) ++count;
    for (int c = col + 1; c < size && cells[row][c] == symbol; ++c) ++count;
    if (count >= WIN_COUNT) return true;


    count = 1;
    for (int r = row - 1; r >= 0 && cells[r][col] == symbol; --r) ++count;
    for (int r = row + 1; r < size && cells[r][col] == symbol; ++r) ++count;
    if (count >= WIN_COUNT) return true;


    if (diagonalWin) {

        count = 1;
        for (int r = row - 1, c = col - 1; r >= 0 && c >= 0 && cells[r][c] == symbol; --r, --c)  ++count;
        for (int r = row + 1, c = col + 1; r < size && c < size && cells[r][c] == symbol; ++r, ++c) ++count;
        if (count >= WIN_COUNT) return true;

        count = 1;
        for (int r = row - 1, c = col + 1; r >= 0 && c < size && cells[r][c] == symbol; --r, ++c) ++count;
        for (int r = row + 1, c = col - 1; r < size && c >= 0 && cells[r][c] == symbol; ++r, --c) ++count;
        if (count >= WIN_COUNT) return true;

    }

    return false;


}




bool Board::isFull() const {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (cells[i][j] == '.')
                return false;
    return true;


}


void Board::draw() const {
    std::cout << "    ";
    for (int j = 0; j < size; ++j)
        std::cout << "  " << static_cast<char>('A' + j) << " " ;
    std::cout << std::endl;

    for (int i = 0; i < size; ++i) {
        std::cout << "    ";
        for (int j = 0; j < size; ++j)
            std::cout << "+---";
        std::cout << "+" << std::endl;

        std::cout << " " << (i+1) << " ";
        for (int j = 0; j < size; ++j) {
            std::cout << " | ";
            if (cells[ i][j] != '.')
                std::cout << cells[i][j];
            else
                std::cout << '.';

        }

        std::cout << " |" << std::endl;
    }

    std::cout << "    ";
    for (int j = 0; j < size; ++j)
        std::cout << "+---";
    std::cout << "+" << std::endl;


}



int Board::getSize() const { return size; }
char Board::getCell(int row, int col) const  { return cells[row][col]; }
void Board::setCell(int row, int col, char ch) {cells[row][col] = ch; }

bool Board::getDiagonalWin() const { return diagonalWin; }









