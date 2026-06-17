#include <iostream>
#include <fstream>
#include <sstream>
#ifdef MEMTRACE
#include "memtrace.h"
#endif
#ifdef CPORTA
#include "gtest_lite.h"
#endif
#include "Game.h"
#include "Figure.h"

int main() {


#ifdef CPORTA


    TEST(Amoba, BoardConstruct) {
        Board b(3, true);
        EXPECT_EQ(3, b.getSize());
        EXPECT_EQ('.', b.getCell(0,0));
    }  ENDM



    TEST(Amoba, PlaceMove) {
        Board b(3, true);
        EXPECT_TRUE(b.placeMove(0,0,'X'));
        EXPECT_EQ('X', b.getCell(0,0));
        EXPECT_FALSE(b.placeMove(0,0,'O'));
    } ENDM


    TEST(Amoba, CheckWinHorizontal) {
        Board b(3, true);
        b.placeMove(0,0,'X');
        b.placeMove(0,1,'X');
        b.placeMove(0,2,'X');
        EXPECT_TRUE(b.checkWin(0,2,'X'));
    } ENDM


    TEST(Amoba, CheckWinVertical) {
        Board b(3, true);
        b.placeMove(0,0,'O');
        b.placeMove(1,0,'O');
        b.placeMove(2,0,'O');
        EXPECT_TRUE(b.checkWin(2,0,'O'));
    } ENDM


    TEST (Amoba, CheckWinDiagonal) {
        Board b(3, true);
        b.placeMove(0,0,'X');
        b.placeMove(1,1,'X');
        b.placeMove(2,2,'X');
        EXPECT_TRUE(b.checkWin(2,2,'X'));
    } ENDM


    TEST(Amoba, IsFull) {
        Board b(2, true);
        b.placeMove(0,0,'X');
        b.placeMove(0,1,'O');
        b.placeMove(1,0,'X');
        b.placeMove(1,1,'O');
        EXPECT_TRUE(b.isFull());
    } ENDM


    TEST(Amoba, BoardExtras) {
        Board b(4, false);
        EXPECT_FALSE(b.getDiagonalWin());
        b.setCell(1, 1, 'X');
        EXPECT_EQ('X', b.getCell(1, 1));
        b.draw();
    } ENDM


    TEST(Amoba, Figures) {
        XFigure x;
        OFigure o;
        EXPECT_EQ('X', x.getSymbol());
        EXPECT_EQ('O', o.getSymbol());
    } ENDM


    TEST(Amoba, ExplicitSaveLoad) {
        std::ofstream out("test_save.dat");
        out << 3 << std::endl << "X.." << std::endl << ".O." << std::endl << "..X" << std::endl << "X" << std::endl << 1 << std::endl;
        out.close();

        Game g;
        EXPECT_TRUE(g.loadGame("test_save.dat"));
        EXPECT_TRUE(g.saveGame("test_save2.dat"));
        EXPECT_FALSE(g.loadGame("nem_letezo_fajl.dat"));
    } ENDM


    TEST(Amoba, GameRunSimulated) {
        std::istringstream sim_input("n\n3\ni\nA1\nB1\nA2\nB2\nA3\nn\n");
        std::streambuf* orig_cin = std::cin.rdbuf(sim_input.rdbuf());

        Game g;
        g.run();

        std::cin.rdbuf(orig_cin);
        SUCCEED();
    } ENDM





#endif


#ifndef CPORTA


    Game game;
    game.run();


#endif


    return 0;
}










