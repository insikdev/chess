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
    void Setup(void);
    void MainTurn(void);
    void Cleanup(void);

private:
    int mTurn { 1 };
    Board mBoard;
    eStatus mState { eStatus::PLAYING };
    Player mWhite { ePieceColor::WHITE };
    Player mBlack { ePieceColor::BLACK };

private:
    bool IsValidStartCoordinate(const Coordinate& start);
    bool IsCheck(Player attacker);

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
