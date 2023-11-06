#pragma once

#include "piece.h"

namespace Chess {
class Queen : public Piece {
public:
    Queen(ePieceColor);
    std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) override final;
};
}