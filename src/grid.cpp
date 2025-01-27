#include "../include/grid.hpp"
#include "../include/constants.hpp"


Grid::Grid(size_t rows, size_t cols) {
    this->rows = rows;
    this->cols = cols;
    makeGrid();
}

void Grid::reset() {
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            grid[i][j] = GRID_PLACEHOLDER;
            hinted[i][j] = false;
        }
    }
}


Grid::~Grid() {
    if (grid != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    if(hinted != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] hinted[i];
        }
        delete[] hinted;
    }
}

void Grid::makeGrid() {
    grid = new char*[rows];
    hinted = new bool*[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new char[cols];
        hinted[i] = new bool[cols];

        for(int j = 0; j < cols; j++) {
            grid[i][j] = GRID_PLACEHOLDER;
            hinted[i][j] = false;
        }
    }
}
