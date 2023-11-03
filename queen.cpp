#include "queen.h"

Chess::Queen::Queen(const Chess::ePieceColor color)
    : Piece(ePieceType::QUEEN, color, color == Chess::ePieceColor::BLACK ? L'\u265B' : L'\u2655')
{
}