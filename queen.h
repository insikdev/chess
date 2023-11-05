#pragma once

#include "piece.h"

namespace Chess {
class Queen : public Piece {
public:
    Queen(ePieceColor);
    std::vector<Position> GetPossiblePositions(Board& board, const Position& current) override final;
};
}