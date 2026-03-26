#include "starter.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <optional>

namespace {
sf::FloatRect getBoardArea(const sf::RenderWindow& window) {
    const sf::Vector2u size = window.getSize();
    const float width = static_cast<float>(size.x);
    const float height = static_cast<float>(size.y);

    const float boardSide = std::min(width, height) * 0.86f;
    const float left = (width - boardSide) * 0.5f;
    const float top = (height - boardSide) * 0.5f;
    return sf::FloatRect(sf::Vector2f(left, top), sf::Vector2f(boardSide, boardSide));
}
}  // namespace

void resetBoard() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = ' ';
        }
    }

    currentPlayer = 'X';
    gameOver = false;
    winner = ' ';
    draw = false;
    hoverRow = -1;
    hoverCol = -1;
}

bool placeMark(int row, int col) {
    if (gameOver) {
        return false;
    }

    if (row < 0 || row > 2 || col < 0 || col > 2) {
        return false;
    }

    if (board[row][col] != ' ') {
        return false;
    }

    board[row][col] = currentPlayer;

    winner = checkWinner();
    if (winner != ' ') {
        gameOver = true;
        draw = false;
        return true;
    }

    if (isBoardFull()) {
        gameOver = true;
        draw = true;
        return true;
    }

    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    return true;
}

bool mapPixelToCell(const sf::RenderWindow& window, int px, int py, int& row, int& col) {
    const sf::FloatRect boardArea = getBoardArea(window);
    const sf::Vector2f point(static_cast<float>(px), static_cast<float>(py));

    if (!boardArea.contains(point)) {
        row = -1;
        col = -1;
        return false;
    }

    const float cellSize = boardArea.size.x / 3.0f;
    col = static_cast<int>((point.x - boardArea.position.x) / cellSize);
    row = static_cast<int>((point.y - boardArea.position.y) / cellSize);

    if (row < 0 || row > 2 || col < 0 || col > 2) {
        row = -1;
        col = -1;
        return false;
    }

    return true;
}

void processEvents(sf::RenderWindow& window) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            window.setView(sf::View(sf::FloatRect(
                sf::Vector2f(0.0f, 0.0f),
                sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)))));
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::R) {
                resetBoard();
                updateWindowTitle(window);
            }
        }

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            if (!mapPixelToCell(window, mouseMoved->position.x, mouseMoved->position.y, hoverRow, hoverCol)) {
                hoverRow = -1;
                hoverCol = -1;
            }
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                int row = -1;
                int col = -1;
                if (mapPixelToCell(window, mousePressed->position.x, mousePressed->position.y, row, col)) {
                    if (placeMark(row, col)) {
                        updateWindowTitle(window);
                    }
                }
            }
        }
    }
}
