#include "king.h"

Chess::King::King(const Chess::ePieceColor color)
    : Piece(ePieceType::KING, color, color == Chess::ePieceColor::BLACK ? L'\u265A' : L'\u2654')
{
}

bool Chess::King::IsValidMove(Board& board, Position current, Position target)
{
    return true;
}