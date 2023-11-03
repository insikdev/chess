#pragma once

#include <string>

namespace Chess {
struct Pos {
    size_t row;
    size_t col;
};

class Utility {
public:
    static bool TryConvertToPos(std::string& input, Pos* out)
    {
        if (input.length() != 2) {
            return false;
        }

        char rank = input[0];
        char file = input[1];

        if ((rank < 'a' || rank > 'h') || (file < '1' || file > '8')) {
            return false;
        }

        out->row = static_cast<size_t>('8' - file);
        out->col = static_cast<size_t>(rank - 'a');
        return true;
    }
};
}