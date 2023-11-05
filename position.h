#pragma once

#include <iostream>
#include <string>

namespace Chess {
class Position {
public:
    Position(char file = 0, char rank = 0)
        : mFile { file }
        , mRank { rank }
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Position& pos)
    {
        os << pos.mFile << pos.mRank;
        return os;
    }

    bool operator==(const Position& rhs) const
    {
        return (mFile == rhs.mFile) && (mRank == rhs.mRank);
    }

    bool GetPositionFromInput(std::string& input)
    {
        char file;
        char rank;

        if (input.length() != 2) {
            return false;
        }

        file = input[0];
        rank = input[1];

        if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
            return false;
        }

        mRank = rank;
        mFile = file;
        return true;
    }

    inline int GetRow() const
    {
        return '8' - mRank;
    }

    inline int GetColumn() const
    {
        return mFile - 'a';
    }

    std::string ToString() const
    {
        std::string str;
        str += mFile;
        str += mRank;
        return str;
    }

    static Position Move(const Position& pos, char dx, char dy)
    {
        return Position { pos.mFile + dx, pos.mRank + dy };
    }

    static bool IsValid(const Position& pos)
    {
        return pos.mFile >= 'a' && pos.mFile <= 'h' && pos.mRank >= '1' && pos.mRank <= '8';
    }

private:
    char mRank;
    char mFile;
};
}