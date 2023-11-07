#pragma once

#include "board.h"
#include "coordinate.h"
#include "shared.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace Chess {
class Piece;

class Player {
public:
    Player(ePieceColor color);
    void InitPieces(Board& board);
    void UpdateAvailablePositions(Board& board);
    Coordinate GetKingPosition(Board& board) const;

public:
    inline ePieceColor GetColor(void) const
    {
        return mColor;
    }

    inline std::vector<Piece*> GetAllPieces(void)
    {
        return mPieces;
    }

    inline std::unordered_map<Coordinate, std::vector<Coordinate>, Coordinate> GetPositionMap(void)
    {
        return mPositionMap;
    }

private:
    const ePieceColor mColor;
    std::vector<Piece*> mPieces;
    std::unordered_map<Coordinate, std::vector<Coordinate>, Coordinate> mPositionMap;
};
}