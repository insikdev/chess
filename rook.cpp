#include "rook.h"
#include "board.h"

using namespace Chess;

Rook::Rook(ePieceColor color)
    : Piece(ePieceType::ROOK, color, color == ePieceColor::BLACK ? L'\u265C' : L'\u2656')
{
}

std::vector<Position> Rook::GetPossiblePositions(Board& board, const Position& current)
{
    std::vector<Position> possiblePositions;

    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };

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