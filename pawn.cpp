#include "pawn.h"
#include "board.h"

using namespace Chess;

Pawn::Pawn(ePieceColor color)
    : Piece(ePieceType::PAWN, color, color == ePieceColor::BLACK ? L'\u265F' : L'\u2659')
{
}

std::vector<Position> Pawn::GetPossiblePositions(Board& board, const Position& current)
{
    std::vector<Position> possiblePositions;

    int forward = (mColor == ePieceColor::WHITE) ? 1 : -1;

    Position forwardOne = Position::Move(current, 0, forward);
    Position forwardTwo = Position::Move(current, 0, 2 * forward);
    Position diagonalLeft = Position::Move(current, -1, forward);
    Position diagonalRight = Position::Move(current, 1, forward);

    if (board.GetPieceOrNull(forwardOne) == nullptr) {
        possiblePositions.push_back(forwardOne);
        if (!mHasMoved && board.GetPieceOrNull(forwardTwo) == nullptr) {
            possiblePositions.push_back(forwardTwo);
        }
    }

    Piece* diagonalLeftPiece = board.GetPieceOrNull(Position::Move(current, -1, forward));
    Piece* diagonalRightPiece = board.GetPieceOrNull(Position::Move(current, 1, forward));

    if (diagonalLeftPiece != nullptr && diagonalLeftPiece->GetColor() != mColor) {
        possiblePositions.push_back(diagonalLeft);
    }

    if (diagonalRightPiece != nullptr && diagonalRightPiece->GetColor() != mColor) {
        possiblePositions.push_back(diagonalRight);
    }

    return possiblePositions;
}