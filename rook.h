#pragma once

#include "piece.h"

namespace Chess {
class Rook : public Piece {
public:
    Rook(ePieceColor);
    std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) override final;
};
}
