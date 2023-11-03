#pragma once

#include "board.h"
#include "shared.h"
#include <vector>

namespace Chess {
class Manager {
public:
    void Run(void);
    int GetNextMove();

private:
    Board mBoard;
    ePieceColor mCurrentPlayer { ePieceColor::WHITE };
    // std::vector<int> mChessNotation;
};
}
