#pragma once

#include "position.h"
#include "shared.h"
#include <vector>

namespace Chess {
class Board;

class Piece {
public:
    Piece(ePieceType type, ePieceColor color, wchar_t unicodePoint)
        : mType { type }
        , mColor { color }
        , mUnicodePoint { unicodePoint } {};

    inline const wchar_t GetUnicodePoint()
    {
        return mUnicodePoint;
    }

    inline const ePieceColor GetColor()
    {
        return mColor;
    };

    // virtual bool IsValidMove(Board& board, Position current, Position target) = 0;

    virtual std::vector<Position> GetPossiblePositions(Board& board, const Position current) = 0;

    bool IsValidMove(std::vector<Position>& possiblePositions, const Position target)
    {
        for (const Position& p : possiblePositions) {
            if (p == target) {
                return true;
            }
        }

        return false;
    }

protected:
    const ePieceType mType;
    const ePieceColor mColor;
    const wchar_t mUnicodePoint;
    bool mHasMoved { false };
};
}
