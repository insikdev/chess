#include "manager.h"
#include "piece.h"
#include <iostream>
#include <string>

using namespace Chess;

void Manager::Init(void)
{
    std::wcout.imbue(std::locale(""));
    mWhite.InitPieces(mBoard);
    mBlack.InitPieces(mBoard);
}

void Manager::Run(void)
{
    while (1) {
        SetupBeforeTurn();
        MainTurn();
        CleanupAfterTurn();
    }
}

void Manager::SetupBeforeTurn(void)
{
    std::cout << "\033[2J\033[1;1H";
    mBoard.Display();
    std::cout << std::endl;
    std::cout << (GetCurrentPlayer().GetColor() == ePieceColor::WHITE ? "백" : "흑") << "의 차례입니다." << std::endl;

    mWhite.UpdateAvailablePositions(mBoard);
    mBlack.UpdateAvailablePositions(mBoard);
}

void Manager::MainTurn(void)
{
    std::string input;
    std::vector<Position> positions;
    Position currentPos;
    Position targetPos;
    Piece* mSelectedPiece;

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

        if (mSelectedPiece->GetColor() != GetCurrentPlayer().GetColor()) {
            std::cout << "내가 소유한 기물이 아닙니다.\n";
            continue;
        }

        positions = GetCurrentPlayer().GetPositionMap()[currentPos.ToString()];

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

void Manager::CleanupAfterTurn()
{
    /* if (IsCheck(mCurrentPlayer)) {
         std::cout << "체크입니다." << std::endl;
         mState = eStatus::CHECK;
     } else {
         mState = eStatus::PLAYING;
     }*/

    mTurn++;
    std::cout << "계속하려면 아무키나 누르세요..." << std::endl;
    std::cin.get();
}

// bool Chess::Manager::IsCheck(ePieceColor currentPlayer)
//{
//     ePieceColor opponentColor = currentPlayer == ePieceColor::WHITE ? ePieceColor::BLACK : ePieceColor::WHITE;
//
//     /*std::vector<Piece*> alivePieces = mBoard.GetAlivePieces(currentPlayer);*/
//     std::vector<Piece*> alivePieces = mCurrentPlayer->GetAllPiecesGetAllPieces();
//     Position opponentKingPos = mBoard.GetKingPosition(opponentColor);
//
//     for (auto* piece : alivePieces) {
//         Position currentPos = mBoard.GetPosition(piece);
//         std::vector<Position> allPos = piece->GetPossiblePositions(mBoard, currentPos);
//
//         for (auto& p : allPos) {
//             if (p == opponentKingPos) {
//                 return true;
//             }
//         }
//     }
//
//     return false;
// }