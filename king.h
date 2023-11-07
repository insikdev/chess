#pragma once

#include "piece.h"

namespace Chess {
class King : public Piece {
public:
    King(ePieceColor);
    std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) override final;
};
}