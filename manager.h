#pragma once

#include "board.h"
#include "player.h"
#include "renderer.h"
#include "shared.h"

namespace Chess {
class Manager {
public:
    void Init(void);
    void Run(void);

private:
    void HandleInput(int ch);
    bool IsValidStartCoordinate(const Coordinate& start);
    bool IsCheck(Player& attacker);
    bool IsCheckmate(Player& attacker);

private:
    int mTurn { 1 };
    std::string mInfo;
    std::vector<Coordinate> mAvailablePositions;
    Coordinate mCurrentCoord { 'a', '1' };
    Coordinate mSelectCoord {};
    Board mBoard;
    Renderer mRenderer;
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
