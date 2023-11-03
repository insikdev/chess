#include "pawn.h"

Chess::Pawn::Pawn(const Chess::ePieceColor color)
    : Piece(ePieceType::PAWN, color, color == Chess::ePieceColor::BLACK ? L'\u265F' : L'\u2659')
{
}