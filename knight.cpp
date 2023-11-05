#include "knight.h"
#include "board.h"

using namespace Chess;

Knight::Knight(ePieceColor color)
    : Piece(ePieceType::KNIGHT, color, color == ePieceColor::BLACK ? L'\u265E' : L'\u2658')
{
}

std::vector<Position> Knight::GetPossiblePositions(Board& board, const Position& current)
{
    std::vector<Position> possiblePositions;

    int dx[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    int dy[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

    for (int i = 0; i < 8; ++i) {
        Position pos = Position::Move(current, dx[i], dy[i]);

        if (Position::IsValid(pos)) {
            Piece* piece = board.GetPieceOrNull(pos);
            if (piece == nullptr || piece->GetColor() != mColor) {
                possiblePositions.push_back(pos);
            }
        }
    }

    return possiblePositions;
}
