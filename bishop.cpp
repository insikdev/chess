#include "bishop.h"
#include "board.h"
#include <vector>

Chess::Bishop::Bishop(const Chess::ePieceColor color)
    : Piece(ePieceType::BISHOP, color, color == Chess::ePieceColor::BLACK ? L'\u265D' : L'\u2657')
{
}

std::vector<Chess::Position> Chess::Bishop::GetPossiblePositions(Board& board, const Position current)
{
    std::vector<Position> possiblePositions;

    int dx[] = { 1, -1, 1, -1 };
    int dy[] = { 1, 1, -1, -1 };

    for (int i = 0; i < 4; ++i) {
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
