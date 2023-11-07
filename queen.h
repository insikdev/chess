#pragma once

#include "piece.h"

namespace Chess {
class Queen : public Piece {
public:
    Queen(ePieceColor);
    std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) override final;
};
}