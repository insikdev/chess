#include "board.h"
#include "piece.h"
#include <iomanip>
#include <iostream>

using namespace Chess;

void Board::Display(void) const
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

Piece* Board::GetPieceOrNull(const Position& pos)
{
    if (!Position::IsValid(pos)) {
        return nullptr;
    }

    return mBoard[pos.GetRow()][pos.GetColumn()];
}

void Board::SetPiece(const Position& pos, Piece* pPiece)
{
    mBoard[pos.GetRow()][pos.GetColumn()] = pPiece;
}

void Board::MovePiece(const Position& from, const Position& to)
{
    mBoard[to.GetRow()][to.GetColumn()] = mBoard[from.GetRow()][from.GetColumn()];
    mBoard[from.GetRow()][from.GetColumn()] = nullptr;
}

Position Board::GetPosition(const Piece* pPiece)
{
    for (char i = 0; i < 8; ++i) {
        for (char j = 0; j < 8; ++j) {
            if (mBoard[i][j] == pPiece) {
                return Position { 'a' + j, '8' - i };
            }
        }
    }

    return Position { 0, 0 };
}
