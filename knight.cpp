#include "knight.h"

Chess::Knight::Knight(const Chess::ePieceColor color)
    : Piece(ePieceType::KNIGHT, color, color == Chess::ePieceColor::BLACK ? L'\u265E' : L'\u2658')
{
}

bool Chess::Knight::IsValidMove(Board& board, Position current, Position target)
{
    return true;
}