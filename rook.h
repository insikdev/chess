#pragma once

#include "piece.h"

namespace Chess {
class Rook : public Piece {
public:
    Rook(ePieceColor);
    std::vector<Position> GetPossiblePositions(Board& board, const Position& current) override final;
};
}
