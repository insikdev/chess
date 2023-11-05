#include "manager.h"
#include "piece.h"
#include <iostream>
#include <string>

void Chess::Manager::Run()
{
    while (1) {
        SetupBeforeTurn();
        SelectPiece();
        CleanupAfterTurn();
    }
}

void Chess::Manager::SetupBeforeTurn()
{
    mSelectedPiece = nullptr;
    std::cout << "\033[2J\033[1;1H";
    mBoard.Display();
    std::cout << std::endl;
    std::cout << (mCurrentPlayer == ePieceColor::WHITE ? "백" : "흑") << "의 차례입니다." << std::endl;
}

void Chess::Manager::CleanupAfterTurn()
{
    std::cout << "계속하려면 아무키나 누르세요..." << std::endl;
    std::cin.get();

    mCurrentPlayer = mCurrentPlayer == ePieceColor::WHITE ? ePieceColor::BLACK : ePieceColor::WHITE;
}

void Chess::Manager::SelectPiece()
{
    std::string input;
    std::vector<Position> positions;
    Position currentPos;
    Position targetPos;

    while (true) {
        std::cout << "움직일 기물의 좌표 : ";
        std::getline(std::cin, input);

        if (currentPos.GetPositionFromInput(input) == false) {
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            continue;
        };

        mSelectedPiece = mBoard.GetPieceOrNull(currentPos);

        if (mSelectedPiece == nullptr) {
            std::cout << "해당 좌표에 기물이 존재하지 않습니다.\n";
            continue;
        }

        if (mSelectedPiece->GetColor() != mCurrentPlayer) {
            std::cout << "내가 소유한 기물이 아닙니다.\n";
            continue;
        }

        positions = mSelectedPiece->GetPossiblePositions(mBoard, currentPos);
        if (positions.empty()) {
            std::cout << "해당 기물은 현재 움직일 수 없습니다." << std::endl;
            continue;
        }

        break;
    }

    while (true) {
        std::cout << "기물이 이동할 좌표 : ";
        std::getline(std::cin, input);

        if (targetPos.GetPositionFromInput(input) == false) {
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            continue;
        };

        if (mSelectedPiece->IsValidMove(positions, targetPos)) {
            mBoard.MovePiece(currentPos, targetPos);
            break;
        } else {
            std::cout << "해당 좌표로 움직일 수 없습니다." << std::endl;
        }
    }
}
