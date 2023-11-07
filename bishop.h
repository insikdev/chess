#pragma once

#include "piece.h"

namespace Chess {
class Bishop : public Piece {
public:
    Bishop(ePieceColor);
    std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) override final;
};
}