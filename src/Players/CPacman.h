#pragma once
#include <cstdio>
#include <ncurses.h>
#include <utility>

/**
 * @brief The Pacman class.
 *
 * This class represents the Pacman character in the game.
 * It manages Pacman's movement, rendering, score, lives, and position.
 */
class CPacman {
public:
    /**
     * @brief Initializes the Pacman character.
     *
     * This function initializes the Pacman character with the specified starting position.
     *
     * @param xPac The x-coordinate of the starting position.
     * @param yPac The y-coordinate of the starting position.
     */
    void init(int xPac, int yPac);
    /**
     * @brief Makes a move for the Pacman character.
     *
     * This function determines the movement of the Pacman character based on user input
     * and updates its position.
     */
    void makeMove();

    /**
     * @brief Renders the Pacman character.
     *
     * This function renders the Pacman character on the specified window.
     *
     * @param win The window to render the Pacman character on.
     */
    void render(WINDOW *win) const;

    /**
     * @brief Respawns the Pacman character.
     *
     * This function respawns the Pacman character at the starting position.
     */
    void respawn();

    int m_Score = 0;
    int m_Lives = 3;
    int m_X;
    int m_Y;
    std::pair<int, int> m_prevPos;
    std::pair<int, int> m_startPos;
};
