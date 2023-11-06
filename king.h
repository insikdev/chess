#pragma once

#include "piece.h"

namespace Chess {
class King : public Piece {
public:
    King(ePieceColor);
    std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) override final;
};
}