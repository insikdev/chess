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

    mRenderer.Init();
}

void Manager::Run(void)
{
    while (mState != eStatus::CHECKMATE) {
        mRenderer.RenderBoard(mBoard, mCurrentCoord, mSelectCoord, mAvailablePositions, mInfo, mTurn);
        HandleInput(getch());
    }

    std::cout << "game end" << std::endl;
}

void Manager::HandleInput(int ch)
{
    switch (ch) {
    case KEY_UP: {
        if (mCurrentCoord.GetRank() == '8') {
            break;
        }
        mCurrentCoord = Coordinate::Move(mCurrentCoord, 0, 1);
        break;
    }
    case KEY_DOWN: {
        if (mCurrentCoord.GetRank() == '1') {
            break;
        }
        mCurrentCoord = Coordinate::Move(mCurrentCoord, 0, -1);
        break;
    }
    case KEY_LEFT: {
        if (mCurrentCoord.GetFile() == 'a') {
            break;
        }
        mCurrentCoord = Coordinate::Move(mCurrentCoord, -1, 0);
        break;
    }
    case KEY_RIGHT: {
        if (mCurrentCoord.GetFile() == 'h') {
            break;
        }
        mCurrentCoord = Coordinate::Move(mCurrentCoord, 1, 0);
        break;
    }
    case 10: {
        // 처음으로 기물을 선택했을 때
        if (!Coordinate::IsValid(mSelectCoord)) {
            if (IsValidStartCoordinate(mCurrentCoord)) {
                mSelectCoord = mCurrentCoord;
                Piece* piece = mBoard.GetPieceOrNull(mSelectCoord);
                mAvailablePositions = piece->GetPossiblePositions(mBoard, mSelectCoord);
                mInfo = "Select " + mCurrentCoord.ToString() + " " + piece->GetTypeToString();
            } else {
                // 좌표가 올바르지 않음
                mInfo = "Not Valid Coordinate : " + mCurrentCoord.ToString();
            }
            break;
        }

        // 기물을 선택 후 이동할 좌표를 입력했을 때
        if (Coordinate::IsInclude(mAvailablePositions, mCurrentCoord)) {
            mBoard.MovePiece(mSelectCoord, mCurrentCoord);
            mWhite.UpdateAvailablePositions(mBoard);
            mBlack.UpdateAvailablePositions(mBoard);

            if (IsCheck(GetOpponentPlayer())) {
                mInfo = "Can't move. Because of check";
                mBoard.UndoMove();
                mWhite.UpdateAvailablePositions(mBoard);
                mBlack.UpdateAvailablePositions(mBoard);
                break;
            }

            // 성공적으로 이동을 마침
            mInfo = "Move to " + mCurrentCoord.ToString();

            if (IsCheck(GetCurrentPlayer())) {
                mInfo += " Check";
                if (IsCheckmate(GetCurrentPlayer())) {
                    mInfo = "Checkmate";
                    mState = eStatus::CHECKMATE;
                    break;
                }
            }

            mSelectCoord = Coordinate { 0, 0 };
            mAvailablePositions.clear();
            mTurn++;
        } else {
            // 이동할 수 없는 좌표를 선택
            mInfo = "Can't Move";
        }

        break;
    }
    case 27: {
        mSelectCoord = Coordinate { 0, 0 };
        mAvailablePositions.clear();
        mInfo.clear();
        break;
    }
    case 'q': {
        endwin(); // ncurses 종료
        break;
    }
    }
}

bool Manager::IsCheck(Player& attacker)
{
    Player& defender = attacker.GetColor() == ePieceColor::WHITE ? mBlack : mWhite;
    Coordinate defenderKingPos = defender.GetKingPosition(mBoard);
    std::unordered_map<Coordinate, std::vector<Coordinate>, Coordinate> positionMap = attacker.GetPositionMap();

    for (const std::pair<Coordinate, std::vector<Coordinate>>& map : positionMap) {
        for (const Coordinate& pos : map.second) {
            if (pos == defenderKingPos) {
                return true;
            }
        }
    }

    return false;
}
bool Manager::IsCheckmate(Player& attacker)
{
    Player& defender = attacker.GetColor() == ePieceColor::WHITE ? mBlack : mWhite;

    const std::unordered_map<Coordinate, std::vector<Coordinate>, Coordinate>& map = defender.GetPositionMap();

    for (const std::pair<Coordinate, std::vector<Coordinate>>& item : map) {
        Coordinate originCoord = item.first;

        for (const Coordinate& availableCoord : item.second) {
            mBoard.MovePiece(originCoord, availableCoord);
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

    if (piece == nullptr) {
        return false;
    }

    if (piece->GetColor() != GetCurrentPlayer().GetColor()) {
        return false;
    }

    return true;
}
