#include "knight.h"
#include "board.h"

using namespace Chess;

Knight::Knight(ePieceColor color)
    : Piece(ePieceType::KNIGHT, color, color == ePieceColor::BLACK ? L'\u265E' : L'\u2658')
{
}

std::vector<Coordinate> Knight::GetPossiblePositions(Board& board, const Coordinate& current)
{
    std::vector<Coordinate> possiblePositions;

    int dx[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    int dy[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

    for (int i = 0; i < 8; ++i) {
        Coordinate pos = Coordinate::Move(current, dx[i], dy[i]);

        if (Coordinate::IsValid(pos)) {
            Piece* piece = board.GetPieceOrNull(pos);
            if (piece == nullptr || piece->GetColor() != mColor) {
                possiblePositions.push_back(pos);
            }
        }
    }

    return possiblePositions;
}
