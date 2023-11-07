#pragma once

#include "coordinate.h"
#include <vector>

namespace Chess {
class Piece;

class Board {
public:
    // void Display(void) const;
    Piece* GetPieceOrNull(const Coordinate& pos);
    Piece* GetPieceOrNull(int x, int y);
    void SetPiece(const Coordinate& pos, Piece* pPiece);
    Coordinate GetPosition(const Piece* pPiece);
    void MovePiece(const Coordinate& from, const Coordinate& to);
    void UndoMove(void);

public:
    const enum { BOARD_SIZE = 8 };

private:
    Piece* mBoard[BOARD_SIZE][BOARD_SIZE] {};
    std::pair<Coordinate, Piece*> mFrom;
    std::pair<Coordinate, Piece*> mTo;
};
}