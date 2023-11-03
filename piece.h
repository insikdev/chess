#pragma once

#include "position.h"
#include "shared.h"

namespace Chess {
class Board;

class Piece {
public:
    Piece(ePieceType type, ePieceColor color, wchar_t unicodePoint)
        : mType { type }
        , mColor { color }
        , mUnicodePoint { unicodePoint } {};

    const wchar_t GetUnicodePoint()
    {
        return mUnicodePoint;
    }

    const ePieceColor GetColor()
    {
        return mColor;
    };

    virtual bool IsValidMove(Board& board, Position current, Position target) = 0;

protected:
    const ePieceType mType;
    const ePieceColor mColor;
    const wchar_t mUnicodePoint;
    bool mHasMoved { false };
};
}
