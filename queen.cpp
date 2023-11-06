#include "queen.h"
#include "board.h"

using namespace Chess;

Queen::Queen(ePieceColor color)
    : Piece(ePieceType::QUEEN, color, color == ePieceColor::BLACK ? L'\u265B' : L'\u2655')
{
}

std::vector<Coordinate> Queen::GetPossiblePositions(Board& board, const Coordinate& current)
{
    std::vector<Coordinate> possiblePositions;

    int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

    for (int i = 0; i < 8; ++i) {
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
