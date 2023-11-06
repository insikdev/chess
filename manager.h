#pragma once

#include "board.h"
#include "player.h"
#include "shared.h"

namespace Chess {
class Manager {
public:
    void Init(void);
    void Run(void);

private:
    void MainTurn(void);
    void Cleanup(void);
    bool IsValidStartCoordinate(const Coordinate& start);
    bool IsCheck(Player& attacker);
    bool IsCheckMate(Player& attacker);
    void RenderPiece(int, int, const Coordinate&, std::vector<Coordinate>&);

private:
    int mTurn { 1 };
    Board mBoard;
    eStatus mState { eStatus::PLAYING };
    Player mWhite { ePieceColor::WHITE };
    Player mBlack { ePieceColor::BLACK };

private:
    inline Player& GetCurrentPlayer(void)
    {
        return mTurn & 1 ? mWhite : mBlack;
    }

    inline Player& GetOpponentPlayer(void)
    {
        return mTurn & 1 ? mBlack : mWhite;
    }
};
}
