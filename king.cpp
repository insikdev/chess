#include "king.h"

Chess::King::King(const Chess::ePieceColor color)
    : Piece(ePieceType::KING, color, color == Chess::ePieceColor::BLACK ? L'\u265A' : L'\u2654')
{
}

std::vector<Chess::Position> Chess::King::GetPossiblePositions(Board& board, const Position current)
{
    std::vector<Position> possiblePositions;
    return possiblePositions;
}
