#pragma once

#include "piece.h"

namespace Chess {
class Knight : public Piece {
public:
    Knight(ePieceColor);
    std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) override final;
};
}