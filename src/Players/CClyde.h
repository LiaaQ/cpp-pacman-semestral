#pragma once
#include "CGhost.h"

/**
 * @brief The CClyde ghost class.
 *
 * This class represents the Clyde ghost in the game.
 * It inherits from the CGhost base class.
 */
class CClyde : public CGhost {
    /**
     * @brief Moves the Clyde ghost in the chase mode.
     *
     * This function determines the movement of the Clyde ghost in the normal mode,
     * using Manhattan distance to determine how to get away.
     *
     * @param pacPos The current position of Pacman.
     * @param map The game map represented as a 2D vector of characters.
     */
    void moveChase(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map,
                   const std::pair<int, int> &prevPacPos) override;

    /**
     * @brief Renders the Clyde ghost.
     *
     * This function renders the Clyde ghost on the specified window.
     *
     * @param win The window to render the Clyde ghost on.
     */
    void render(WINDOW *win) const override;

    void renderFrightened(WINDOW *win) const override;

private:
    std::pair<int, int> m_targetCell = {-1, -1};
};
