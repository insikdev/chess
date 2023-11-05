#include "king.h"
#include "board.h"

Chess::King::King(const Chess::ePieceColor color)
    : Piece(ePieceType::KING, color, color == Chess::ePieceColor::BLACK ? L'\u265A' : L'\u2654')
{
}

std::vector<Chess::Position> Chess::King::GetPossiblePositions(Board& board, const Position current)
{
    std::vector<Position> possiblePositions;

    int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

    for (int i = 0; i < 8; ++i) {
        Position pos = Position::Move(current, dx[i], dy[i]);
        if (Position::IsValid(pos)) {
            Piece* piece = board.GetPieceOrNull(pos);
            if (piece == nullptr || piece->GetColor() != mColor) {
                possiblePositions.push_back(pos);
            }
        }
    }
    // TODO: 체크 상황 추가

    return possiblePositions;
}
