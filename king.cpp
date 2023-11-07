#include "king.h"

using namespace Chess;

King::King(ePieceColor color)
    : Piece(ePieceType::KING, color, color == ePieceColor::BLACK ? L'\u265A' : L'\u2654')
{
}

std::vector<Coordinate> King::GetAllPossibleMoves(Board& board, const Coordinate& currentCoord)
{
    std::vector<Coordinate> possibleCoords;

    int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

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
