#pragma once

#include "position.h"
#include <vector>

namespace Chess {
class Piece;

class Board {
public:
    void Display(void) const;
    Piece* GetPieceOrNull(const Position& pos);
    void SetPiece(const Position& pos, Piece* pPiece);
    Position GetPosition(const Piece* pPiece);
    void MovePiece(const Position& from, const Position& to);

private:
    Piece* mBoard[8][8] {};
};
}