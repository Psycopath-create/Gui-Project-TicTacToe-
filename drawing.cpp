#include "starter.h"

#include <SFML/Graphics.hpp>
#include <algorithm>

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

void drawX(sf::RenderWindow& window, const sf::FloatRect& cellRect, float thickness) {
    const sf::Color xColor(235, 80, 80);
    const float margin = cellRect.size.x * 0.22f;
    const float armLength = cellRect.size.x - (margin * 2.0f);

    sf::RectangleShape arm1(sf::Vector2f(armLength, thickness));
    arm1.setFillColor(xColor);
    arm1.setOrigin(sf::Vector2f(armLength * 0.5f, thickness * 0.5f));
    arm1.setPosition(sf::Vector2f(cellRect.position.x + (cellRect.size.x * 0.5f), cellRect.position.y + (cellRect.size.y * 0.5f)));
    arm1.setRotation(sf::degrees(45.0f));
    window.draw(arm1);

    sf::RectangleShape arm2(sf::Vector2f(armLength, thickness));
    arm2.setFillColor(xColor);
    arm2.setOrigin(sf::Vector2f(armLength * 0.5f, thickness * 0.5f));
    arm2.setPosition(sf::Vector2f(cellRect.position.x + (cellRect.size.x * 0.5f), cellRect.position.y + (cellRect.size.y * 0.5f)));
    arm2.setRotation(sf::degrees(-45.0f));
    window.draw(arm2);
}

void drawO(sf::RenderWindow& window, const sf::FloatRect& cellRect, float stroke) {
    const sf::Color oColor(100, 210, 145);
    const float radius = (cellRect.size.x * 0.5f) - (cellRect.size.x * 0.24f);
    sf::CircleShape ring(radius);
    ring.setFillColor(sf::Color::Transparent);
    ring.setOutlineThickness(stroke);
    ring.setOutlineColor(oColor);
    ring.setOrigin(sf::Vector2f(radius, radius));
    ring.setPosition(sf::Vector2f(cellRect.position.x + (cellRect.size.x * 0.5f), cellRect.position.y + (cellRect.size.y * 0.5f)));
    window.draw(ring);
}
}  // namespace

void drawGrid(sf::RenderWindow& window) {
    const sf::Vector2u size = window.getSize();

    sf::RectangleShape background(sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
    background.setFillColor(sf::Color(22, 27, 35));
    window.draw(background);

    const sf::FloatRect boardArea = getBoardArea(window);
    const float cellSize = boardArea.size.x / 3.0f;
    const float lineThickness = std::max(3.0f, boardArea.size.x * 0.01f);
    const float symbolStroke = std::max(6.0f, boardArea.size.x * 0.015f);

    sf::RectangleShape boardFrame(sf::Vector2f(boardArea.size.x, boardArea.size.y));
    boardFrame.setPosition(sf::Vector2f(boardArea.position.x, boardArea.position.y));
    boardFrame.setFillColor(sf::Color(29, 35, 45));
    window.draw(boardFrame);

    if (!gameOver && hoverRow >= 0 && hoverCol >= 0 && board[hoverRow][hoverCol] == ' ') {
        sf::RectangleShape hoverCell(sf::Vector2f(cellSize, cellSize));
        hoverCell.setPosition(sf::Vector2f(boardArea.position.x + (hoverCol * cellSize), boardArea.position.y + (hoverRow * cellSize)));
        hoverCell.setFillColor(sf::Color(255, 255, 255, 24));
        window.draw(hoverCell);
    }

    sf::RectangleShape line;
    line.setFillColor(sf::Color(235, 240, 245));

    for (int i = 1; i <= 2; ++i) {
        line.setSize(sf::Vector2f(boardArea.size.x, lineThickness));
        line.setPosition(sf::Vector2f(boardArea.position.x, boardArea.position.y + (i * cellSize) - (lineThickness * 0.5f)));
        window.draw(line);

        line.setSize(sf::Vector2f(lineThickness, boardArea.size.y));
        line.setPosition(sf::Vector2f(boardArea.position.x + (i * cellSize) - (lineThickness * 0.5f), boardArea.position.y));
        window.draw(line);
    }

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            const sf::FloatRect cellRect(
                sf::Vector2f(boardArea.position.x + (col * cellSize), boardArea.position.y + (row * cellSize)),
                sf::Vector2f(cellSize, cellSize));

            if (board[row][col] == 'X') {
                drawX(window, cellRect, symbolStroke);
            } else if (board[row][col] == 'O') {
                drawO(window, cellRect, symbolStroke);
            }
        }
    }
}