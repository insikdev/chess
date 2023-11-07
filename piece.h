#pragma once

#include "coordinate.h"
#include "shared.h"
#include <unordered_map>
#include <vector>

namespace Chess {
class Board;

class Piece {
public:
    Piece(ePieceType type, ePieceColor color, wchar_t unicodePoint);
    virtual std::vector<Coordinate> GetPossiblePositions(Board& board, const Coordinate& current) = 0;

public:
    inline ePieceType GetType() const
    {
        return mType;
    }

    inline std::string GetTypeToString() const
    {
        std::unordered_map<ePieceType, std::string> map = {
            { ePieceType::BISHOP, "Bishop" },
            { ePieceType::KING, "King" },
            { ePieceType::KNIGHT, "Knight" },
            { ePieceType::PAWN, "Pawn" },
            { ePieceType::QUEEN, "Queen" },
            { ePieceType::ROOK, "Rook" }
        };

        return map[mType];
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
