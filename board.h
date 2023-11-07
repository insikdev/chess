#pragma once

#include "coordinate.h"
#include <vector>

namespace Chess {
class Piece;

class Board {
public:
    void Display(void) const;
    Piece* GetPieceOrNull(const Coordinate&) const;
    Coordinate GetCoord(const Piece*) const;
    void SetPiece(const Coordinate&, Piece*);
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