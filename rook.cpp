#include "rook.h"
#include "board.h"

using namespace Chess;

Rook::Rook(ePieceColor color)
    : Piece(ePieceType::ROOK, color, color == ePieceColor::BLACK ? L'\u265C' : L'\u2656')
{
}

std::vector<Coordinate> Rook::GetPossiblePositions(Board& board, const Coordinate& current)
{
    std::vector<Coordinate> possiblePositions;

    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };

    for (int i = 0; i < 4; ++i) {
        Coordinate pos = Coordinate::Move(current, dx[i], dy[i]);

        while (Coordinate::IsValid(pos)) {
            Piece* piece = board.GetPieceOrNull(pos);

            if (piece == nullptr) {
                possiblePositions.push_back(pos);
                pos = Coordinate::Move(pos, dx[i], dy[i]);
                continue;
            } else {
                if (piece->GetColor() != mColor) {
                    possiblePositions.push_back(pos);
                }
                break;
            }
        }
    }

    return possiblePositions;
}