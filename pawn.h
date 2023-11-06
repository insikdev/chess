#pragma once

#include "piece.h"

namespace Chess {
class Pawn : public Piece {
public:
    Pawn(ePieceColor);
    std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) override final;
};
}