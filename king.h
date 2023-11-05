#pragma once

#include "piece.h"

namespace Chess {
class King : public Piece {
public:
    King(ePieceColor);
    std::vector<Position> GetPossiblePositions(Board& board, const Position& current) override final;
};
}