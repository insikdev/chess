#include "pawn.h"
#include "board.h"
#include <vector>

Chess::Pawn::Pawn(const Chess::ePieceColor color)
    : Piece(ePieceType::PAWN, color, color == Chess::ePieceColor::BLACK ? L'\u265F' : L'\u2659')
{
}

bool Chess::Pawn::IsValidMove(Board& board, const Position current, const Position target)
{
    std::vector<Position> validMoves;

    int forward = (mColor == ePieceColor::WHITE) ? 1 : -1;

    Position forwardOne = Position::MoveVertical(current, forward);
    Position forwardTwo = Position::MoveVertical(current, 2 * forward);
    Position diagonalLeft = Position::Move(current, -1, forward);
    Position diagonalRight = Position::Move(current, 1, forward);

    if (board.GetPiece(forwardOne) == nullptr) {
        validMoves.push_back(forwardOne);
        if (!mHasMoved && board.GetPiece(forwardTwo) == nullptr) {
            validMoves.push_back(forwardTwo);
        }
    }

    Piece* diagonalLeftPiece = board.GetPiece(Position::Move(current, -1, forward));
    Piece* diagonalRightPiece = board.GetPiece(Position::Move(current, 1, forward));

    if (diagonalLeftPiece != nullptr && diagonalLeftPiece->GetColor() != mColor) {
        validMoves.push_back(diagonalLeft);
    }

    if (diagonalRightPiece != nullptr && diagonalRightPiece->GetColor() != mColor) {
        validMoves.push_back(diagonalRight);
    }

    for (const Position& move : validMoves) {
        if (move == target) {
            return true;
        }
    }

    return false;
}