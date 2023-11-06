#pragma once

#include "piece.h"

namespace Chess {
class Bishop : public Piece {
public:
    Bishop(ePieceColor);
    std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) override final;
};
}