#include "king.h"
#include "board.h"

using namespace Chess;

King::King(ePieceColor color)
    : Piece(ePieceType::KING, color, color == ePieceColor::BLACK ? L'\u265A' : L'\u2654')
{
}

std::vector<Coordinate> King::GetPossiblePositions(Board& board, const Coordinate& current)
{
    std::vector<Coordinate> possiblePositions;

    int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

    for (int i = 0; i < 8; ++i) {
        Coordinate pos = Coordinate::Move(current, dx[i], dy[i]);
        if (Coordinate::IsValid(pos)) {
            Piece* piece = board.GetPieceOrNull(pos);
            if (piece == nullptr || piece->GetColor() != mColor) {
                possiblePositions.push_back(pos);
            }
        }
    }
    // TODO: 체크 상황 추가

    return possiblePositions;
}
