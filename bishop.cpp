#include "bishop.h"

Chess::Bishop::Bishop(const Chess::ePieceColor color)
    : Piece(ePieceType::BISHOP, color, color == Chess::ePieceColor::BLACK ? L'\u265D' : L'\u2657')
{
}