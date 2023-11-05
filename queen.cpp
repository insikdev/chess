#include "queen.h"
#include "board.h"

Chess::Queen::Queen(const Chess::ePieceColor color)
    : Piece(ePieceType::QUEEN, color, color == Chess::ePieceColor::BLACK ? L'\u265B' : L'\u2655')
{
}

std::vector<Chess::Position> Chess::Queen::GetPossiblePositions(Board& board, const Position current)
{
    std::vector<Position> possiblePositions;

    int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

    for (int i = 0; i < 8; ++i) {
        Position pos = Position::Move(current, dx[i], dy[i]);

        while (Position::IsValid(pos)) {
            Piece* piece = board.GetPieceOrNull(pos);

            if (piece == nullptr) {
                possiblePositions.push_back(pos);
                pos = Position::Move(pos, dx[i], dy[i]);
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
