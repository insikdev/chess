#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Chess {
class Coordinate {
public:
    Coordinate(char file = 0, char rank = 0);
    bool operator==(const Coordinate& rhs) const;
    size_t operator()(const Coordinate& coord) const;
    std::string ToString() const;

public:
    inline int GetRow() const
    {
        return '8' - mRank;
    }

    inline int GetColumn() const
    {
        return mFile - 'a';
    }

    inline char GetRank() const
    {
        return mRank;
    }

    inline char GetFile() const
    {
        return mFile;
    }

    static inline Coordinate Move(const Coordinate& coord, char dx, char dy)
    {
        return Coordinate { coord.mFile + dx, coord.mRank + dy };
    }

    static bool IsValid(const Coordinate& coord)
    {
        if (coord.mFile < 'a' || coord.mFile > 'h' || coord.mRank < '1' || coord.mRank > '8') {
            return false;
        }

        return true;
    }

    static bool IsInclude(const std::vector<Coordinate>& coords, const Coordinate& input)
    {
        for (const Coordinate& c : coords) {
            if (c == input) {
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