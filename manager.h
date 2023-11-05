#pragma once

#include "board.h"
#include "shared.h"

namespace Chess {
class Manager {
public:
    void Run(void);
    void SetupBeforeTurn(void);
    void SelectPiece(void);
    void CleanupAfterTurn(void);

private:
    Board mBoard;
    ePieceColor mCurrentPlayer { ePieceColor::WHITE };
    Piece* mSelectedPiece {};
};
}
