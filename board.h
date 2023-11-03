#pragma once

#include "position.h"

namespace Chess {
class Piece;
class Board {
public:
    Board(void);
    ~Board();
    void Display(void);
    Piece* GetPiece(const Position&);
    void MovePiece(Position, Position);

private:
    Piece* mBoard[8][8] {};
};
}