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
                std::cout << '.';
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

Piece* Board::GetPieceOrNull(const Coordinate& coord) const
{
    if (!Coordinate::IsValid(coord)) {
        return nullptr;
    }

    return mBoard[coord.GetRow()][coord.GetColumn()];
}

Coordinate Board::GetCoord(const Piece* pPiece) const
{
    for (char i = 0; i < BOARD_SIZE; ++i) {
        for (char j = 0; j < BOARD_SIZE; ++j) {
            if (mBoard[i][j] == pPiece) {
                return Coordinate { 'a' + j, '8' - i };
            }
        }
    }

    return Coordinate { 0, 0 };
}

void Board::SetPiece(const Coordinate& coord, Piece* pPiece)
{
    mBoard[coord.GetRow()][coord.GetColumn()] = pPiece;
}

void Board::MovePiece(const Coordinate& from, const Coordinate& to)
{
    mFrom.first = from;
    mFrom.second = GetPieceOrNull(from);
    mTo.first = to;
    mTo.second = GetPieceOrNull(to);

    mBoard[to.GetRow()][to.GetColumn()] = mBoard[from.GetRow()][from.GetColumn()];
    mBoard[from.GetRow()][from.GetColumn()] = nullptr;
}

void Board::UndoMove(void)
{
    SetPiece(mFrom.first, mFrom.second);
    SetPiece(mTo.first, mTo.second);
}