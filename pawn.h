#pragma once

#include "piece.h"

namespace Chess {
class Pawn : public Piece {
public:
    Pawn(ePieceColor);
    std::vector<Position> GetPossiblePositions(Board& board, const Position& current) override final;
};
}