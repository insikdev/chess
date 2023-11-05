#include "position.h"

using namespace Chess;

Position::Position(char file, char rank)
    : mFile { file }
    , mRank { rank }
{
}

bool Position::operator==(const Position& rhs) const
{
    return (mFile == rhs.mFile) && (mRank == rhs.mRank);
}

bool Position::GetPositionFromInput(std::string& input)
{
    if (input.length() != 2) {
        return false;
    }

    char file = input[0];
    char rank = input[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return false;
    }

    mRank = rank;
    mFile = file;
    return true;
}

std::string Position::ToString() const
{
    std::string str;
    str += mFile;
    str += mRank;
    return str;
}