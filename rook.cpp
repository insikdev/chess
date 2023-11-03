#include "Rook.h"

Chess::Rook::Rook(const Chess::ePieceColor color)
    : Piece(ePieceType::ROOK, color, color == Chess::ePieceColor::BLACK ? L'\u265C' : L'\u2656')
{
}