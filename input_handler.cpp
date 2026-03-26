#include "starter.h"

#include <iostream>

void resetBoard() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = ' ';
        }
    }
}

bool placeMark(int row, int col, char player) {
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        std::cout << "Invalid position. Use values from 1 to 3.\n";
        return false;
    }

    if (board[row][col] != ' ') {
        std::cout << "Cell is already taken. Try another move.\n";
        return false;
    }

    board[row][col] = player;
    return true;
}
