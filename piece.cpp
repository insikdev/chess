#include "piece.h"

using namespace Chess;

Piece::Piece(ePieceType type, ePieceColor color, wchar_t unicodePoint)
    : mType { type }
    , mColor { color }
    , mUnicodePoint { unicodePoint }
{
}

bool Piece::IsValidMove(std::vector<Position>& possiblePositions, const Position target)
{
    for (const auto& p : possiblePositions) {
        if (p == target) {
            return true;
        }
    }

    return false;
}