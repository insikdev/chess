#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include <iomanip>
#include <iostream>

Chess::Board::Board()
{
    std::wcout.imbue(std::locale(""));

    for (int i = 0; i < 8; i++) {
        mBoard[1][i] = new Chess::Pawn(Chess::ePieceColor::BLACK);
        mBoard[6][i] = new Chess::Pawn(Chess::ePieceColor::WHITE);
    }

    mBoard[0][0] = new Chess::Rook(Chess::ePieceColor::BLACK);
    mBoard[0][7] = new Chess::Rook(Chess::ePieceColor::BLACK);
    mBoard[7][0] = new Chess::Rook(Chess::ePieceColor::WHITE);
    mBoard[7][7] = new Chess::Rook(Chess::ePieceColor::WHITE);

    mBoard[0][4] = new Chess::King(Chess::ePieceColor::BLACK);
    mBoard[7][4] = new Chess::King(Chess::ePieceColor::WHITE);

    mBoard[0][3] = new Chess::Queen(Chess::ePieceColor::BLACK);
    mBoard[7][3] = new Chess::Queen(Chess::ePieceColor::WHITE);

    mBoard[0][1] = new Chess::Knight(Chess::ePieceColor::BLACK);
    mBoard[0][6] = new Chess::Knight(Chess::ePieceColor::BLACK);
    mBoard[7][1] = new Chess::Knight(Chess::ePieceColor::WHITE);
    mBoard[7][6] = new Chess::Knight(Chess::ePieceColor::WHITE);

    mBoard[0][2] = new Chess::Bishop(Chess::ePieceColor::BLACK);
    mBoard[0][5] = new Chess::Bishop(Chess::ePieceColor::BLACK);
    mBoard[7][2] = new Chess::Bishop(Chess::ePieceColor::WHITE);
    mBoard[7][5] = new Chess::Bishop(Chess::ePieceColor::WHITE);
}

Chess::Board::~Board()
{
    /*for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            free(mBoard[i][j]);
        }
    }*/
}

void Chess::Board::Display()
{
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << " ";

        for (int j = 0; j < 8; ++j) {
            if (mBoard[i][j]) {
                std::wcout << mBoard[i][j]->GetUnicodePoint();
            } else {
                std::cout << ' ';
            }
        }

        std::cout << std::endl;
    }
    std::cout << std::setw(10) << "abcdefgh" << std::endl;
}

Chess::Piece* Chess::Board::GetPiece(Pos pos)
{
    return mBoard[pos.row][pos.col];
}

void Chess::Board::MovePiece(Pos current, Pos target)
{
    mBoard[target.row][target.col] = mBoard[current.row][current.col];
    mBoard[current.row][current.col] = nullptr;
}
