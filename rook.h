#pragma once

#include "piece.h"

namespace Chess {
class Rook : public Piece {
public:
    Rook(ePieceColor);
    std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) override final;
};
}
