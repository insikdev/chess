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
};
}
