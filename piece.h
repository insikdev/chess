#pragma once

#include "shared.h"

namespace Chess {
enum class ePieceColor {
    WHITE,
    BLACK
};

enum class ePieceType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
};

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

    // virtual bool CanMove(Pos current, Pos target);

private:
    const ePieceType mType;
    const ePieceColor mColor;
    const wchar_t mUnicodePoint;
};
}
