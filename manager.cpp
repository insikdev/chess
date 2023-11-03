#include "manager.h"
#include <iostream>
#include <string>

void Chess::Manager::Run()
{
    while (1) {
        std::cout << "\033[2J\033[1;1H";
        mBoard.Display();
        GetNextMove();
        std::cout << "계속하려면 아무키나 누르세요..." << std::endl;
        std::cin.get();
    }
}

int Chess::Manager::GetNextMove()
{
    std::string input;
    Pos currentPos;
    Pos targetPos;
    Chess::Piece* currentPiece;

    std::cout << std::endl;
    std::cout << (mCurrentPlayer == ePieceColor::WHITE ? "백" : "흑") << "의 차례입니다." << std::endl;

    while (true) {
        std::cout << "움직일 기물의 좌표 : ";
        std::getline(std::cin, input);

        if (Utility::TryConvertToPos(input, &currentPos) == false) {
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            continue;
        };

        currentPiece = mBoard.GetPiece(currentPos);

        if (currentPiece == nullptr) {
            std::cout << "해당 좌표에 기물이 존재하지 않습니다.\n";
            continue;
        }

        if (currentPiece->GetColor() != mCurrentPlayer) {
            std::cout << "내가 소유한 기물이 아닙니다.\n";
            continue;
        }

        break;
    }

    while (true) {
        std::cout << "기물이 이동할 좌표 : ";
        std::getline(std::cin, input);

        if (Utility::TryConvertToPos(input, &targetPos) == false) {
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            continue;
        };

        // 선택한 기물이 지정한 위치로 움직일 수 있는지 확인하는 함수
        mBoard.MovePiece(currentPos, targetPos);
        break;
    }

    mCurrentPlayer = mCurrentPlayer == ePieceColor::WHITE ? ePieceColor::BLACK : ePieceColor::WHITE;
    return 0;
}