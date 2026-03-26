#include "starter.h"

#include <SFML/Graphics.hpp>
#include <iostream>

char board[3][3];
char currentPlayer = 'X';
bool gameOver = false;
char winner = ' ';
bool draw = false;
int hoverRow = -1;
int hoverCol = -1;

void updateWindowTitle(sf::RenderWindow& window) {
    if (gameOver && winner != ' ') {
        window.setTitle(std::string("Tic Tac Toe - Player ") + winner + " wins! (Press R to restart)");
        return;
    }

    if (gameOver && draw) {
        window.setTitle("Tic Tac Toe - Draw! (Press R to restart)");
        return;
    }

    window.setTitle(std::string("Tic Tac Toe - Turn: ") + currentPlayer + " (Press R to restart)");
}

int main() {
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(960, 720)),
        "Tic Tac Toe",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setVerticalSyncEnabled(true);

    resetBoard();
    updateWindowTitle(window);

    while (window.isOpen()) {
        processEvents(window);

        window.clear();
        drawGrid(window);
        window.display();
    }

    return 0;
}
