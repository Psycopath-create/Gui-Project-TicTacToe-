#include "starter.h"

#include <cctype>
#include <iostream>
#include <limits>

namespace {
bool askPlayAgain() {
    std::cout << "Play again? (y/n): ";
    char answer = 'n';
    std::cin >> answer;
    answer = static_cast<char>(std::tolower(static_cast<unsigned char>(answer)));
    return answer == 'y';
}

void clearInputState() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
}  // namespace

char board[3][3];

int main() {
    std::cout << "Tic-Tac-Toe (X O)\n";
    std::cout << "Enter row and column numbers from 1 to 3.\n";

    bool keepPlaying = true;
    while (keepPlaying) {
        resetBoard();
        char currentPlayer = 'X';

        while (true) {
            drawGrid();
            std::cout << "Player " << currentPlayer << " move (row col): ";

            int row = 0;
            int col = 0;
            if (!(std::cin >> row >> col)) {
                std::cout << "Please enter two numbers.\n";
                clearInputState();
                continue;
            }

            if (!placeMark(row - 1, col - 1, currentPlayer)) {
                continue;
            }

            const char winner = checkWinner();
            if (winner != ' ') {
                drawGrid();
                std::cout << "Player " << winner << " wins!\n";
                break;
            }

            if (isBoardFull()) {
                drawGrid();
                std::cout << "It's a draw!\n";
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        keepPlaying = askPlayAgain();
    }

    std::cout << "Thanks for playing.\n";
    return 0;
}
