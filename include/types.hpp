#pragma once

#include <cstddef>
#include "constants.hpp"

enum Orientation {
    HORIZONTAL,
    VERTICAL
};

struct Coordinate {
    size_t row;
    size_t col;
};

