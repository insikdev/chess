#include "piece.h"

using namespace Chess;

Piece::Piece(ePieceType type, ePieceColor color, wchar_t unicodePoint)
    : mType { type }
    , mColor { color }
    , mUnicodePoint { unicodePoint }
{
}
