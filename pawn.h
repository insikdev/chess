#pragma once

#include "piece.h"

namespace Chess {
class Pawn : public Piece {
public:
    Pawn(const Chess::ePieceColor);
    // bool IsValidMove(Board& board, Position current, Position target) override;
    std::vector<Position> GetPossiblePositions(Board& board, const Position current) override final;

private:
};
}