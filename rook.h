#pragma once

#include "piece.h"

namespace Chess {
class Rook : public Piece {
public:
    Rook(const Chess::ePieceColor);
    // bool IsValidMove(Board& board, Position current, Position target) override;
    std::vector<Position> GetPossiblePositions(Board& board, const Position current) override final;

private:
};
}
