#include "queen.h"

using namespace Chess;

Queen::Queen(ePieceColor color)
    : Piece(ePieceType::QUEEN, color, color == ePieceColor::BLACK ? L'\u265B' : L'\u2655')
{
}

std::vector<Coordinate> Queen::GetAllPossibleMoves(Board& board, const Coordinate& currentCoord)
{
    std::vector<Coordinate> possibleCoords;

    int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

    for (int i = 0; i < 8; ++i) {
        Coordinate coord = Coordinate::Move(currentCoord, dx[i], dy[i]);

        while (Coordinate::IsValid(coord)) {
            Piece* piece = board.GetPieceOrNull(coord);

            if (piece == nullptr) {
                possibleCoords.push_back(coord);
                coord = Coordinate::Move(coord, dx[i], dy[i]);
                continue;
            } else {
                if (piece->GetColor() != mColor) {
                    possibleCoords.push_back(coord);
                }
                break;
            }
        }
    }

    return possibleCoords;
}
