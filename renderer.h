#pragma once

#include "board.h"
#include "coordinate.h"
#include <curses.h>

namespace Chess {

class Renderer {
public:
    void Init(void);
    void RenderBoard(Board& board, const Coordinate& current, const Coordinate& select, std::vector<Coordinate> availablePositions, const std::string& info, int turn);

private:
    void RenderPiece(Board& board, const Coordinate& currentCoord, const Coordinate& selectCoord, std::vector<Coordinate>& availablePositions);

private:
    const enum { SPACE = 2 };
};
}