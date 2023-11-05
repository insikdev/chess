#pragma once

#include "piece.h"

namespace Chess {
class Bishop : public Piece {
public:
    Bishop(ePieceColor);
    std::vector<Position> GetPossiblePositions(Board& board, const Position& current) override final;
};
}