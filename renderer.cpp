#include "renderer.h"
#include "board.h"
#include "piece.h"
#include <iostream>

using namespace Chess;

void Renderer::Init()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(2, COLOR_RED, COLOR_BLACK); // 기물 선택했을 때
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // 선택한 기물이 이동할 수 있는 위치
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}

void Renderer::RenderBoard(Board& board, const Coordinate& current, const Coordinate& from, std::vector<Coordinate> availablePositions, const std::string& info, int turn)
{
    clear();

    for (int i = 0; i < board.BOARD_SIZE; i++) {
        mvaddch(8, i * 2 + SPACE, 'a' + i);
        mvaddch(i, 0, '8' - i);
    }

    for (char i = 0; i < board.BOARD_SIZE; i++) {
        for (char j = 0; j < board.BOARD_SIZE; j++) {
            RenderPiece(board, Coordinate { 'a' + i, '8' - j }, from, availablePositions);
        }
    }

    // mvprintw(10, 0, "Coordinate : %c%c", current.GetFile(), current.GetRank());
    mvprintw(10, 0, "%s Turn", (turn & 1) ? "WHITE" : "BLACK");
    mvprintw(12, 0, "Info : %s", info.c_str());

    RenderPiece(board, current, from, availablePositions);
}

void Renderer::RenderPiece(Board& board, const Coordinate& currentCoord, const Coordinate& selectCoord, std::vector<Coordinate>& availablePositions)
{
    Piece* piece = board.GetPieceOrNull(currentCoord);

    wchar_t unicodePoint = (piece == nullptr) ? L'\u002E' : piece->GetUnicodePoint();

    if (selectCoord == currentCoord) {
        attron(COLOR_PAIR(1));
        mvaddch(currentCoord.GetRow(), currentCoord.GetColumn() * 2 + SPACE, unicodePoint);
        attroff(COLOR_PAIR(1));
    } else {
        mvaddch(currentCoord.GetRow(), currentCoord.GetColumn() * 2 + SPACE, unicodePoint);
    }

    if (!availablePositions.empty() && Coordinate::IsInclude(availablePositions, currentCoord)) {
        attron(COLOR_PAIR(2));
        mvaddch(currentCoord.GetRow(), currentCoord.GetColumn() * 2 + SPACE, unicodePoint);
        attroff(COLOR_PAIR(2));
    }
}