#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Chess {
class Position {
public:
    Position(char file = 0, char rank = 0);
    bool operator==(const Position& rhs) const;
    bool GetPositionFromInput(std::string& input);
    std::string ToString() const;

public:
    friend std::ostream& operator<<(std::ostream& os, const Position& pos)
    {
        os << pos.mFile << pos.mRank;
        return os;
    }

    inline int GetRow() const
    {
        return '8' - mRank;
    }

    inline int GetColumn() const
    {
        return mFile - 'a';
    }

    static Position Move(const Position& pos, char dx, char dy)
    {
        return Position { pos.mFile + dx, pos.mRank + dy };
    }

    static bool IsValid(const Position& pos)
    {
        return pos.mFile >= 'a' && pos.mFile <= 'h' && pos.mRank >= '1' && pos.mRank <= '8';
    }

    static bool IsInclude(const std::vector<Position>& positions, const Position& input)
    {
        for (const auto& p : positions) {
            if (p == input) {
                return true;
            }
        }

        return false;
    }

private:
    char mRank;
    char mFile;
};
}