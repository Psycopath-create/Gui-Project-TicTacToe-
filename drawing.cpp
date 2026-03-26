#include "starter.h"

#include <iostream>

void drawGrid() {
    std::cout << "\n   1   2   3\n";
    for (int row = 0; row < 3; ++row) {
        std::cout << " " << (row + 1) << " ";
        for (int col = 0; col < 3; ++col) {
            std::cout << board[row][col];
            if (col < 2) {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        if (row < 2) {
            std::cout << "   ---------\n";
        }
    }
    std::cout << "\n";
}