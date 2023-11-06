#include "bishop.h"
#include "board.h"

using namespace Chess;

Bishop::Bishop(ePieceColor color)
    : Piece(ePieceType::BISHOP, color, color == ePieceColor::BLACK ? L'\u265D' : L'\u2657')
{
}

std::vector<Coordinate> Bishop::GetPossiblePositions(Board& board, const Coordinate& current)
{
    std::vector<Coordinate> possiblePositions;

    int dx[] = { 1, -1, 1, -1 };
    int dy[] = { 1, 1, -1, -1 };

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
