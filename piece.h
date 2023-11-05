#pragma once

#include "position.h"
#include "shared.h"
#include <vector>

namespace Chess {
class Board;

class Piece {
public:
    Piece(ePieceType type, ePieceColor color, wchar_t unicodePoint);
    virtual std::vector<Position> GetPossiblePositions(Board& board, const Position& current) = 0;

public:
    inline ePieceType GetType() const
    {
        return mType;
    }

    inline ePieceColor GetColor() const
    {
        return mColor;
    }

    inline wchar_t GetUnicodePoint() const
    {
        return mUnicodePoint;
    }

protected:
    const ePieceType mType;
    const ePieceColor mColor;
    const wchar_t mUnicodePoint;
    bool mHasMoved { false };
};
}
