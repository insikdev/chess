#include "bishop.h"

using namespace Chess;

Bishop::Bishop(ePieceColor color)
    : Piece(ePieceType::BISHOP, color, color == ePieceColor::BLACK ? L'\u265D' : L'\u2657')
{
}

std::vector<Coordinate> Bishop::GetAllPossibleMoves(Board& board, const Coordinate& currentCoord)
{
    std::vector<Coordinate> possibleCoords;

    int dx[] = { 1, -1, 1, -1 };
    int dy[] = { 1, 1, -1, -1 };

    for (int i = 0; i < 4; ++i) {
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
