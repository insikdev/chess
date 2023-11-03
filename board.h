#pragma once

#include "piece.h"

namespace Chess {
class Board {
public:
    Board(void);
    ~Board();
    void Display(void);
    Piece* GetPiece(Pos);
    void MovePiece(Pos, Pos);

private:
    Piece* mBoard[8][8] {};
};
}