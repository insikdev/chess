#include "queen.h"

Chess::Queen::Queen(const Chess::ePieceColor color)
    : Piece(ePieceType::QUEEN, color, color == Chess::ePieceColor::BLACK ? L'\u265B' : L'\u2655')
{
}

bool Chess::Queen::IsValidMove(Board& board, Position current, Position target)
{
    return true;
}