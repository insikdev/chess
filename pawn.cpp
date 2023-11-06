#include "pawn.h"
#include "board.h"

using namespace Chess;

Pawn::Pawn(ePieceColor color)
    : Piece(ePieceType::PAWN, color, color == ePieceColor::BLACK ? L'\u265F' : L'\u2659')
{
}

std::vector<Coordinate> Pawn::GetPossiblePositions(Board& board, const Coordinate& current)
{
    std::vector<Coordinate> possiblePositions;

    int forward = (mColor == ePieceColor::WHITE) ? 1 : -1;

    Coordinate forwardOne = Coordinate::Move(current, 0, forward);
    Coordinate forwardTwo = Coordinate::Move(current, 0, 2 * forward);
    Coordinate diagonalLeft = Coordinate::Move(current, -1, forward);
    Coordinate diagonalRight = Coordinate::Move(current, 1, forward);

    Piece* forwardOnePiece = board.GetPieceOrNull(forwardOne);
    Piece* forwardTwoPiece = board.GetPieceOrNull(forwardTwo);

    if (forwardOnePiece == nullptr) {
        possiblePositions.push_back(forwardOne);

        if (!mHasMoved && forwardTwoPiece == nullptr) {
            possiblePositions.push_back(forwardTwo);
        }
    }

    Piece* diagonalLeftPiece = board.GetPieceOrNull(diagonalLeft);
    Piece* diagonalRightPiece = board.GetPieceOrNull(diagonalRight);

    if (diagonalLeftPiece != nullptr && diagonalLeftPiece->GetColor() != mColor) {
        possiblePositions.push_back(diagonalLeft);
    }

    if (diagonalRightPiece != nullptr && diagonalRightPiece->GetColor() != mColor) {
        possiblePositions.push_back(diagonalRight);
    }

    return possiblePositions;
}