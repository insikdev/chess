#pragma once

#include "piece.h"

namespace Chess {
class Knight : public Piece {
public:
    Knight(ePieceColor);
    std::vector<Position> GetPossiblePositions(Board& board, const Position& current) override final;
};
}