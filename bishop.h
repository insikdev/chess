#pragma once

#include "piece.h"

namespace Chess {
class Bishop : public Piece {
public:
    Bishop(const Chess::ePieceColor);
    bool IsValidMove(Board& board, Position current, Position target) override;

private:
};
}