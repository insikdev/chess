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
    mWhite.UpdateAvailablePositions(mBoard);
    mBlack.UpdateAvailablePositions(mBoard);
}

void Manager::Run(void)
{
    while (1) {
        Setup();
        MainTurn();
        Cleanup();
    }
}

void Manager::Setup(void)
{

    std::cout << "\033[2J\033[1;1H";
    mBoard.Display();
    std::cout << std::endl;
    std::cout << (GetCurrentPlayer().GetColor() == ePieceColor::WHITE ? "백" : "흑") << "의 차례입니다." << std::endl;

    std::cout << std::cin.get() << std::endl;
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

void Manager::Cleanup()
{
    if (IsCheck(GetCurrentPlayer())) {
        std::cout << "체크입니다." << std::endl;
        mState = eStatus::CHECK;
    } else {
        mState = eStatus::PLAYING;
    }

    mTurn++;
    std::cout << "계속하려면 아무키나 누르세요..." << std::endl;
    std::cin.get();
}

bool Manager::IsCheck(Player attacker)
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

bool Manager::IsValidStartCoordinate(const Coordinate& start)
{
    Piece* piece = mBoard.GetPieceOrNull(start);

    if (piece == nullptr) {
        std::cout << "해당 좌표에 기물이 존재하지 않습니다.\n";
        return false;
    }

    if (piece->GetColor() != GetCurrentPlayer().GetColor()) {
        std::cout << "내가 소유한 기물이 아닙니다.\n";
        return false;
    }

    return true;
}
