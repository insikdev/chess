#include "knight.h"

using namespace Chess;

Knight::Knight(ePieceColor color)
    : Piece(ePieceType::KNIGHT, color, color == ePieceColor::BLACK ? L'\u265E' : L'\u2658')
{
}

std::vector<Coordinate> Knight::GetAllPossibleMoves(Board& board, const Coordinate& currentCoord)
{
    std::vector<Coordinate> possibleCoords;

    int dx[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    int dy[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

    for (int i = 0; i < 8; ++i) {
        Coordinate coord = Coordinate::Move(currentCoord, dx[i], dy[i]);

        if (Coordinate::IsValid(coord)) {
            Piece* piece = board.GetPieceOrNull(coord);
            if (piece == nullptr || piece->GetColor() != mColor) {
                possibleCoords.push_back(coord);
            }
        }
    }

    return possibleCoords;
}
