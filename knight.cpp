#include "knight.h"

Chess::Knight::Knight(const Chess::ePieceColor color)
    : Piece(ePieceType::KNIGHT, color, color == Chess::ePieceColor::BLACK ? L'\u265E' : L'\u2658')
{
}