#pragma once

#include "board.h"
#include "coordinate.h"
#include "shared.h"
#include <unordered_map>
#include <vector>

namespace Chess {
class Piece {
public:
    Piece(ePieceType, ePieceColor, wchar_t);
    virtual std::vector<Coordinate> GetAllPossibleMoves(Board&, const Coordinate&) = 0;

public:
    inline ePieceType GetType() const
    {
        return mType;
    }

    inline std::string GetTypeToString() const
    {
        std::unordered_map<ePieceType, std::string> types = {
            { ePieceType::BISHOP, "Bishop" },
            { ePieceType::KING, "King" },
            { ePieceType::KNIGHT, "Knight" },
            { ePieceType::PAWN, "Pawn" },
            { ePieceType::QUEEN, "Queen" },
            { ePieceType::ROOK, "Rook" }
        };

        return types[mType];
    }

    inline ePieceColor GetColor() const
    {
        return mColor;
    }

    inline wchar_t GetUnicodePoint() const
    {
        return mUnicodePoint;
    }

    inline void HandleMove()
    {
        mHasMoved = true;
    }

protected:
    const ePieceType mType;
    const ePieceColor mColor;
    const wchar_t mUnicodePoint;
    bool mHasMoved { false };
};
}
