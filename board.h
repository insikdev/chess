#pragma once

#include "coordinate.h"
#include <vector>

namespace Chess {
class Piece;

class Board {
public:
    void Display(void) const;
    Piece* GetPieceOrNull(const Coordinate& pos);
    void SetPiece(const Coordinate& pos, Piece* pPiece);
    Coordinate GetPosition(const Piece* pPiece);
    void MovePiece(const Coordinate& from, const Coordinate& to);

private:
    Piece* mBoard[8][8] {};
};
}