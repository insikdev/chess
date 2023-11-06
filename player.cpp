#include "player.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "shared.h"

using namespace Chess;

Player::Player(ePieceColor color)
    : mColor { color }
{
    mPieces.reserve(16);
}

void Player::InitPieces(Board& board)
{
    const char pawnRank = mColor == ePieceColor::WHITE ? '2' : '7';
    const char backRank = mColor == ePieceColor::WHITE ? '1' : '8';

    std::vector<std::pair<Coordinate, Piece*>> pieces;
    for (char i = 0; i < 8; ++i) {
        pieces.push_back(std::make_pair(Coordinate { 'a' + i, pawnRank }, new Pawn { mColor }));
    }

    pieces.push_back(std::make_pair(Coordinate { 'a', backRank }, new Rook { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'b', backRank }, new Knight { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'c', backRank }, new Bishop { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'd', backRank }, new Queen { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'e', backRank }, new King { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'f', backRank }, new Bishop { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'g', backRank }, new Knight { mColor }));
    pieces.push_back(std::make_pair(Coordinate { 'h', backRank }, new Rook { mColor }));

    for (const auto& p : pieces) {
        board.SetPiece(p.first, p.second);
        mPieces.push_back(p.second);
    }
}

Coordinate Player::GetKingPosition(Board& board) const
{
    for (auto* p : mPieces) {
        if (p->GetType() == ePieceType::KING) {
            return board.GetPosition(p);
        }
    }

    return Coordinate {};
}

void Player::UpdateAvailablePositions(Board& board)
{
    mPositionMap.clear();

    for (auto* piece : mPieces) {
        Coordinate currentPos = board.GetPosition(piece);
        mPositionMap[currentPos.ToString()] = piece->GetPossiblePositions(board, currentPos);
    }
}