#pragma once

#include "piece.h"

namespace Chess {
class Pawn : public Piece {
public:
    Pawn(ePieceColor);
    std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) override final;
};
}