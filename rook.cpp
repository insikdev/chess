#include "rook.h"

using namespace Chess;

Rook::Rook(ePieceColor color)
    : Piece(ePieceType::ROOK, color, color == ePieceColor::BLACK ? L'\u265C' : L'\u2656')
{
}

std::vector<Coordinate> Rook::GetAllPossibleMoves(Board& board, const Coordinate& currentCoord)
{
    std::vector<Coordinate> possibleCoords;

    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };

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