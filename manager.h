#pragma once

#include "board.h"
#include "player.h"
#include "shared.h"
#include <unordered_map>

namespace Chess {
class Manager {
public:
    void Init(void);
    void Run(void);

private:
    void SetupBeforeTurn(void);
    void MainTurn(void);
    void CleanupAfterTurn(void);
    bool IsCheck(Player attacker);

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
