#pragma once

#include <string>

namespace Chess {
class Position {
public:
    Position(char rank = 0, char file = 0)
        : mRank { rank }
        , mFile { file }
    {
    }

    Position& operator=(const Position& rhs) = default;

    bool operator==(const Position& rhs) const
    {
        return (mRank == rhs.mRank) && (mFile == rhs.mFile);
    }

    bool GetPositionFromInput(std::string& input)
    {
        char rank;
        char file;

        if (input.length() != 2) {
            return false;
        }

        rank = input[0];
        file = input[1];

        if ((rank < 'a' || rank > 'h') || (file < '1' || file > '8')) {
            return false;
        }

        mRank = rank;
        mFile = file;
        return true;
    }

    inline int GetRow() const
    {
        return '8' - mFile;
    }

    inline int GetColumn() const
    {
        return mRank - 'a';
    }

    static Position MoveVertical(const Position& pos, char dy)
    {
        return Position { pos.mRank, pos.mFile + dy };
    }

    static Position Movehorizontal(const Position& pos, char dx)
    {
        return Position { pos.mRank + dx, pos.mFile };
    }

    static Position Move(const Position& pos, char dx, char dy)
    {
        return Position { pos.mRank + dx, pos.mFile + dy };
    }

public:
    char mRank;
    char mFile;
};
}