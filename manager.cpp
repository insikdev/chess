#include "manager.h"
#include "piece.h"
#include <curses.h>
#include <iostream>
#include <string>

using namespace Chess;

void Manager::Init(void)
{
    mWhite.InitPieces(mBoard);
    mBlack.InitPieces(mBoard);
    mWhite.UpdateAvailablePositions(mBoard);
    mBlack.UpdateAvailablePositions(mBoard);

    setlocale(LC_ALL, ""); // 유니코드 문자를 지원하도록 로케일 설정
    initscr(); // ncurses 초기화
    noecho(); // 입력한 문자를 화면에 표시하지 않음
    cbreak(); // 한 문자씩 입력 받음
    keypad(stdscr, TRUE); // 화살표 키 활성화
    start_color(); // 색상 사용을 위한 초기화
    init_pair(2, COLOR_RED, COLOR_BLACK); // 기물 선택했을 때
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // 선택한 기물이 이동할 수 있는 위치
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}

void Manager::Run(void)
{
    const char* files = "abcdefgh";
    const char* ranks = "87654321";
    const int BOARD_SIZE = 8;
    const int SPACE = 2;
    int x = 0;
    int y = 0;
    ePhase phase = ePhase::PHASE1;
    std::string info;

    Coordinate currentCoord;
    Coordinate fromCoord;
    Coordinate toCoord;
    std::vector<Coordinate> availablePositions;

    while (true) {
        if (mState == eStatus::CHECKMATE) {
            break;
        }
        clear();
        currentCoord = Coordinate { files[x], ranks[y] };

        for (int i = 0; i < BOARD_SIZE; i++) {
            mvaddch(8, i * 2 + SPACE, files[i]);
            mvaddch(i, 0, ranks[i]);
        }

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                // 1. 체스 보드를 렌더링
                RenderPiece(i, j, fromCoord, availablePositions);
            }
        }

        mvprintw(10, 0, "Coordinate : %s", currentCoord.ToString().c_str());
        mvprintw(12, 0, "%s Turn", (mTurn & 1) ? "WHITE" : "BLACK");
        mvprintw(14, 0, "Info : %s", info.c_str());

        // 2. 이동하는 화살표를 렌더링
        RenderPiece(y, x, fromCoord, availablePositions);

        refresh();
        int ch = getch(); // 사용자 입력 대기

        switch (ch) {
        case KEY_UP:
            if (y > 0)
                y--;
            break;
        case KEY_DOWN:
            if (y < BOARD_SIZE - 1)
                y++;
            break;
        case KEY_LEFT:
            if (x > 0)
                x--;
            break;
        case KEY_RIGHT:
            if (x < BOARD_SIZE - 1)
                x++;
            break;
        case 10: {
            Coordinate coord = Coordinate { files[x], ranks[y] };

            if (phase == ePhase::PHASE1) {
                if (IsValidStartCoordinate(coord)) {
                    fromCoord = coord;
                    Piece* piece = mBoard.GetPieceOrNull(fromCoord);
                    availablePositions = piece->GetPossiblePositions(mBoard, fromCoord);

                    phase = ePhase::PHASE2;
                } else {
                    // 좌표가 올바르지 않음
                }
            } else if (phase == ePhase::PHASE2) {
                if (Coordinate::IsInclude(availablePositions, coord)) {
                    mBoard.MovePiece(fromCoord, coord);
                    mWhite.UpdateAvailablePositions(mBoard);
                    mBlack.UpdateAvailablePositions(mBoard);

                    if (IsCheck(GetOpponentPlayer())) {
                        info = "Can't move. Because of check";
                        mBoard.UndoMove();
                        mWhite.UpdateAvailablePositions(mBoard);
                        mBlack.UpdateAvailablePositions(mBoard);
                        break;
                    }

                    if (IsCheck(GetCurrentPlayer())) {
                        info = "Check";
                        if (IsCheckMate(GetCurrentPlayer())) {
                            info = "Checkmate";
                            mState = eStatus::CHECKMATE;
                            break;
                        }
                    }

                    mTurn++;
                    phase = ePhase::PHASE1;
                    fromCoord = Coordinate { 0, 0 };
                    toCoord = Coordinate { 0, 0 };
                    availablePositions.clear();
                } else {
                    // 이동할 수 없는 좌표를 선택
                }
            }

            break;
        }
        case 27: {
            fromCoord = Coordinate { 0, 0 };
            toCoord = Coordinate { 0, 0 };
            availablePositions.clear();
            phase = ePhase::PHASE1;
            break;
        }
        case 'q':
            endwin(); // ncurses 종료
            break;
        }
    }
    std::cout << "game end" << std::endl;
}

void Manager::RenderPiece(int i, int j, const Coordinate& fromCoord, std::vector<Coordinate>& availablePositions)
{
    const char* files = "abcdefgh";
    const char* ranks = "87654321";
    const int SPACE = 2;
    Piece* piece = mBoard.GetPieceOrNull(i, j);
    Coordinate coord = Coordinate { files[j], ranks[i] };

    wchar_t unicodePoint = piece == nullptr ? L'\u002E' : piece->GetUnicodePoint();

    if (fromCoord == coord) {
        attron(COLOR_PAIR(1));
        mvaddch(i, j * 2 + SPACE, unicodePoint);
        attroff(COLOR_PAIR(1));
    } else {
        mvaddch(i, j * 2 + SPACE, unicodePoint);
        attroff(COLOR_PAIR(1));
    }

    if (!availablePositions.empty() && Coordinate::IsInclude(availablePositions, coord)) {
        attron(COLOR_PAIR(2));
        mvaddch(i, j * 2 + SPACE, unicodePoint);
        attroff(COLOR_PAIR(2));
    }
}

void Manager::MainTurn(void)
{
    std::vector<Coordinate> availablePositions;
    Coordinate start;
    Coordinate destination;

    while (true) {
    phase1:
        start = Coordinate::GetCoordinateFromInput("움직일 기물의 좌표 : ");
        if (!IsValidStartCoordinate(start)) {
            goto phase1;
        }

        availablePositions = GetCurrentPlayer().GetPositionMap()[start.ToString()];

        if (availablePositions.empty()) {
            std::cout << "해당 기물은 현재 움직일 수 없습니다." << std::endl;
            goto phase1;
        }

        { // print all coordinate
            for (auto& p : availablePositions) {
                std::cout << p << ' ';
            }
            std::cout << std::endl;
        }

    phase2:
        destination = Coordinate::GetCoordinateFromInput("기물이 이동할 좌표 : ");

        if (!Coordinate::IsInclude(availablePositions, destination)) {
            std::cout << "해당 좌표로 움직일 수 없습니다." << std::endl;
            goto phase2;
        }

        mBoard.MovePiece(start, destination);
        mWhite.UpdateAvailablePositions(mBoard);
        mBlack.UpdateAvailablePositions(mBoard);

        if (mState == eStatus::CHECK && IsCheck(GetOpponentPlayer())) {
            mBoard.MovePiece(destination, start);
            mWhite.UpdateAvailablePositions(mBoard);
            mBlack.UpdateAvailablePositions(mBoard);
            std::cout << "체크 입니다. 다른 수를 시도하세요" << std::endl;
            goto phase1;
        } else {
            goto finish;
        }
    }

finish:
    mState = eStatus::PLAYING;
    mBoard.GetPieceOrNull(destination)->HandleMove();
}

// void Manager::Cleanup()
//{
//     if (IsCheck(GetCurrentPlayer())) {
//         std::cout << "체크입니다." << std::endl;
//         mState = eStatus::CHECK;
//     } else {
//         mState = eStatus::PLAYING;
//     }
//
//     mTurn++;
//     std::cout << "계속하려면 아무키나 누르세요..." << std::endl;
//     std::cin.get();
// }

bool Manager::IsCheck(Player& attacker)
{
    Player& defender = attacker.GetColor() == ePieceColor::WHITE ? mBlack : mWhite;
    Coordinate defenderKingPos = defender.GetKingPosition(mBoard);
    std::unordered_map<std::string, std::vector<Coordinate>> positionMap = attacker.GetPositionMap();

    for (const auto& map : positionMap) {
        for (const auto& pos : map.second) {
            if (pos == defenderKingPos) {
                return true;
            }
        }
    }

    return false;
}

bool Manager::IsCheckMate(Player& attacker)
{
    Player& defender = attacker.GetColor() == ePieceColor::WHITE ? mBlack : mWhite;

    const std::unordered_map<std::string, std::vector<Coordinate>>& map = defender.GetPositionMap();

    for (const std::pair<std::string, std::vector<Coordinate>>& item : map) {
        Coordinate coord = Coordinate { item.first[0], item.first[1] };

        for (const Coordinate& availableCoord : item.second) {
            mBoard.MovePiece(coord, availableCoord);
            mWhite.UpdateAvailablePositions(mBoard);
            mBlack.UpdateAvailablePositions(mBoard);
            if (!IsCheck(attacker)) {
                mBoard.UndoMove();
                mWhite.UpdateAvailablePositions(mBoard);
                mBlack.UpdateAvailablePositions(mBoard);
                return false;
            } else {
                mBoard.UndoMove();
                mWhite.UpdateAvailablePositions(mBoard);
                mBlack.UpdateAvailablePositions(mBoard);
            }
        }
    }

    return true;
}

bool Manager::IsValidStartCoordinate(const Coordinate& coord)
{
    Piece* piece = mBoard.GetPieceOrNull(coord);

    if (piece == nullptr) { // 해당 좌표에 기물이 없을 때
        return false;
    }

    if (piece->GetColor() != GetCurrentPlayer().GetColor()) { // 해당 좌표의 기물이 내가 소유한 기물이 아닐 때
        return false;
    }

    return true;
}
