#include "pawn.h"

using namespace Chess;

Pawn::Pawn(ePieceColor color)
    : Piece(ePieceType::PAWN, color, color == ePieceColor::BLACK ? L'\u265F' : L'\u2659')
{
}

std::vector<Coordinate> Pawn::GetAllPossibleMoves(Board& board, const Coordinate& currentCoord)
{
    std::vector<Coordinate> possibleCoords;

    int forward = (mColor == ePieceColor::WHITE) ? 1 : -1;

    Coordinate forwardOne = Coordinate::Move(currentCoord, 0, forward);
    Coordinate forwardTwo = Coordinate::Move(currentCoord, 0, 2 * forward);
    Coordinate diagonalLeft = Coordinate::Move(currentCoord, -1, forward);
    Coordinate diagonalRight = Coordinate::Move(currentCoord, 1, forward);

    Piece* forwardOnePiece = board.GetPieceOrNull(forwardOne);
    Piece* forwardTwoPiece = board.GetPieceOrNull(forwardTwo);

    if (forwardOnePiece == nullptr) {
        possibleCoords.push_back(forwardOne);

        if (!mHasMoved && forwardTwoPiece == nullptr) {
            possibleCoords.push_back(forwardTwo);
        }
    }

    Piece* diagonalLeftPiece = board.GetPieceOrNull(diagonalLeft);
    Piece* diagonalRightPiece = board.GetPieceOrNull(diagonalRight);

    if (diagonalLeftPiece != nullptr && diagonalLeftPiece->GetColor() != mColor) {
        possibleCoords.push_back(diagonalLeft);
    }

    if (diagonalRightPiece != nullptr && diagonalRightPiece->GetColor() != mColor) {
        possibleCoords.push_back(diagonalRight);
    }

    return possibleCoords;
}