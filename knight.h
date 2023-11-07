#pragma once

#include "piece.h"

namespace Chess {
class Knight : public Piece {
public:
    Knight(ePieceColor);
    std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) override final;
};
}