#pragma once

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

enum class eStatus {
    PLAYING,
    CHECK,
    CHECKMATE,
};
}