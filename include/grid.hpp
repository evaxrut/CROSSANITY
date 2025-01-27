#pragma once
#include <cstddef>


class Grid {
public:
    // default constructor
    Grid(size_t rows, size_t cold);

    // deleted copy constructor
    Grid(const Grid &other) = delete;

    // deleted move constructor
    Grid(const Grid &&other) = delete;

    ~Grid();

    void reset();

    char ** grid;
    bool ** hinted;

    size_t rows;
    size_t cols;

private:
    void makeGrid();
};