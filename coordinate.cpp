#include "coordinate.h"

using namespace Chess;

Coordinate::Coordinate(char file, char rank)
    : mFile { file }
    , mRank { rank }
{
}

bool Coordinate::operator==(const Coordinate& rhs) const
{
    return (mFile == rhs.mFile) && (mRank == rhs.mRank);
}

size_t Coordinate::operator()(const Coordinate& coord) const
{
    return coord.GetRow() * 8 + coord.GetColumn();
}

std::string Coordinate::ToString() const
{
    std::string str;
    str += mFile;
    str += mRank;
    return str;
}