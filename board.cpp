#include "board.h"
#include "piece.h"
#include <iomanip>
#include <iostream>

using namespace Chess;

void Board::Display(void) const
{
    for (int i = 0; i < 8; ++i) {
        std::wcout << 8 - i << L'\u2009';

        for (int j = 0; j < 8; ++j) {
            if (mBoard[i][j]) {
                std::wcout << mBoard[i][j]->GetUnicodePoint();
            } else {
                std::cout << ' ';
            }
            std::wcout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

Piece* Board::GetPieceOrNull(const Coordinate& pos)
{
    if (!Coordinate::IsValid(pos)) {
        return nullptr;
    }

    return mBoard[pos.GetRow()][pos.GetColumn()];
}

void Board::SetPiece(const Coordinate& pos, Piece* pPiece)
{
    mBoard[pos.GetRow()][pos.GetColumn()] = pPiece;
}

void Board::MovePiece(const Coordinate& from, const Coordinate& to)
{
    mBoard[to.GetRow()][to.GetColumn()] = mBoard[from.GetRow()][from.GetColumn()];
    mBoard[from.GetRow()][from.GetColumn()] = nullptr;
}

Coordinate Board::GetPosition(const Piece* pPiece)
{
    for (char i = 0; i < 8; ++i) {
        for (char j = 0; j < 8; ++j) {
            if (mBoard[i][j] == pPiece) {
                return Coordinate { 'a' + j, '8' - i };
            }
        }
    }

    return Coordinate { 0, 0 };
}
