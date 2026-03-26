#ifndef STARTER_H
#define STARTER_H

#include <string>
#include <vector>

// This is the "Blueprint" for each player
struct Player {
    std::string name;
    char symbol;      
    int wins = 0;
    int losses = 0;
};

// This stores a single move (Row 0-2, Col 0-2)
struct Move {
    int row;
    int col;
    char symbol;
};

// This is the "Brain" of the game
struct GameState {
    char board[3][3];       // The 2D array requirement
    bool isXTurn = true;
    std::vector<Move> history; // For the Replay requirement
};

// Shared board state used by drawing, input, and game logic.
extern char board[3][3];

void drawGrid();
void resetBoard();
bool placeMark(int row, int col, char player);

char checkWinner();
bool isBoardFull();

void saveStats(const Player& p);
void loadStats(Player& p);

#endif
