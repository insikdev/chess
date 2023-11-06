#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Chess {
class Coordinate {
public:
    Coordinate(char file = 0, char rank = 0);
    bool operator==(const Coordinate& rhs) const;
    std::string ToString() const;

public:
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& pos)
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

    static inline Coordinate Move(const Coordinate& pos, char dx, char dy)
    {
        return Coordinate { pos.mFile + dx, pos.mRank + dy };
    }

    static bool IsValid(const Coordinate& pos)
    {
        return pos.mFile >= 'a' && pos.mFile <= 'h' && pos.mRank >= '1' && pos.mRank <= '8';
    }

    static bool IsInclude(const std::vector<Coordinate>& positions, const Coordinate& input)
    {
        for (const auto& p : positions) {
            if (p == input) {
                return true;
            }
        }

        return false;
    }

    static Coordinate GetCoordinateFromInput(const std::string& prompt)
    {
        std::string str;

        while (true) {
            std::cout << prompt;
            std::getline(std::cin, str);

            if (str.length() != 2) {
                std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
                continue;
            }

            char file = str[0];
            char rank = str[1];

            Coordinate out { file, rank };
            if (!Coordinate::IsValid(out)) {
                std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
                continue;
            }

            return out;
        }
    }

private:
    char mRank;
    char mFile;
};
}